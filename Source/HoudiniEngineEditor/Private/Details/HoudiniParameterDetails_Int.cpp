/*
* Copyright (c) <2017> Side Effects Software Inc.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#include "HoudiniApi.h"
#include "HoudiniParameterDetails.h"
#include "HoudiniAssetComponentDetails.h"
#include "HoudiniEngineEditorPrivatePCH.h"

#include "HoudiniAssetComponent.h"
#include "Parameters/HoudiniAssetInput.h"
#include "Parameters/HoudiniAssetInstanceInput.h"
#include "HoudiniAssetInstanceInputField.h"

#include "Parameters/HoudiniAssetParameterButton.h"
#include "Parameters/HoudiniAssetParameterChoice.h"
#include "Parameters/HoudiniAssetParameterColor.h"
#include "Parameters/HoudiniAssetParameterFile.h"
#include "Parameters/HoudiniAssetParameterFolder.h"
#include "Parameters/HoudiniAssetParameterFolderList.h"
#include "Parameters/HoudiniAssetParameterFloat.h"
#include "Parameters/HoudiniAssetParameterInt.h"
#include "Parameters/HoudiniAssetParameterLabel.h"
#include "Parameters/HoudiniAssetParameterMultiparm.h"
#include "Parameters/HoudiniAssetParameterRamp.h"
#include "Parameters/HoudiniAssetParameterSeparator.h"
#include "Parameters/HoudiniAssetParameterString.h"
#include "Parameters/HoudiniAssetParameterToggle.h"

#include "HoudiniRuntimeSettings.h"

#include "Widgets/SNewFilePathPicker.h"

#include "CurveEditorSettings.h"
#include "DetailLayoutBuilder.h"
#include "Editor/SceneOutliner/Public/SceneOutlinerModule.h"
#include "Editor/SceneOutliner/Public/SceneOutlinerPublicTypes.h"
#include "Editor/UnrealEd/Public/AssetThumbnail.h"
#include "Editor/UnrealEd/Public/Layers/ILayers.h"
#include "Editor/PropertyEditor/Public/PropertyCustomizationHelpers.h"
#include "Editor/PropertyEditor/Private/PropertyNode.h"
#include "Editor/PropertyEditor/Private/SDetailsViewBase.h"
#include "EditorDirectories.h"
#include "Engine/Selection.h"
#include "Engine/SkeletalMesh.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Internationalization/Internationalization.h"
#include "IDetailGroup.h"
#include "Particles/ParticleSystemComponent.h"
#include "SCurveEditor.h"
#include "SAssetDropTarget.h"
#include "Sound/SoundBase.h"
#include "Math/UnitConversion.h"
#include "Widgets/Colors/SColorPicker.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/NumericUnitTypeInterface.inl"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Widgets/Input/SRotatorInputBox.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SUniformGridPanel.h"


#define LOCTEXT_NAMESPACE HOUDINI_LOCTEXT_NAMESPACE

void
FHoudiniParameterDetails::CreateWidgetInt(IDetailCategoryBuilder & LocalDetailCategoryBuilder, class UHoudiniAssetParameterInt& InParam)
{
    TWeakObjectPtr<UHoudiniAssetParameterInt> MyParam(&InParam);
    FDetailWidgetRow & Row = LocalDetailCategoryBuilder.AddCustomRow(FText::GetEmpty());

    // Create the standard parameter name widget.
    CreateNameWidget(&InParam, Row, true);

    TSharedRef< SVerticalBox > VerticalBox = SNew(SVerticalBox);

    // Helper function to find a unit from a string (name or abbreviation) 
    TOptional<EUnit> ParmUnit = FUnitConversion::UnitFromString(*InParam.ValueUnit);

    TSharedPtr<INumericTypeInterface<int32>> TypeInterface;
    if (FUnitConversion::Settings().ShouldDisplayUnits() && ParmUnit.IsSet())
    {
        TypeInterface = MakeShareable(new TNumericUnitTypeInterface<int32>(ParmUnit.GetValue()));
    }

    for (int32 Idx = 0; Idx < InParam.GetTupleSize(); ++Idx)
    {
        TSharedPtr< SNumericEntryBox< int32 > > NumericEntryBox;

        VerticalBox->AddSlot().Padding(2, 2, 5, 2)
            [
                SAssignNew(NumericEntryBox, SNumericEntryBox< int32 >)
                .AllowSpin(true)

            .Font(FEditorStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))

            .MinValue(InParam.ValueMin)
            .MaxValue(InParam.ValueMax)

            .MinSliderValue(InParam.ValueUIMin)
            .MaxSliderValue(InParam.ValueUIMax)

            .Value(TAttribute< TOptional< int32 > >::Create(
                TAttribute< TOptional< int32 > >::FGetter::CreateUObject(
                    &InParam, &UHoudiniAssetParameterInt::GetValue, Idx)))
            .OnValueChanged(SNumericEntryBox< int32 >::FOnValueChanged::CreateLambda(
                [=](int32 Val) {
            MyParam->SetValue(Val, Idx, false, false);
        }))
            .OnValueCommitted(SNumericEntryBox< int32 >::FOnValueCommitted::CreateLambda(
                [=](float Val, ETextCommit::Type TextCommitType) {
            MyParam->SetValue(Val, Idx, true, true);
        }))
            .OnBeginSliderMovement(FSimpleDelegate::CreateUObject(
                &InParam, &UHoudiniAssetParameterInt::OnSliderMovingBegin, Idx))
            .OnEndSliderMovement(SNumericEntryBox< int32 >::FOnValueChanged::CreateUObject(
                &InParam, &UHoudiniAssetParameterInt::OnSliderMovingFinish, Idx))

            .SliderExponent(1.0f)
            .TypeInterface(TypeInterface)
            ];

        if (NumericEntryBox.IsValid())
            NumericEntryBox->SetEnabled(!InParam.bIsDisabled);
    }

    Row.ValueWidget.Widget = VerticalBox;
    Row.ValueWidget.MinDesiredWidth(HAPI_UNREAL_DESIRED_ROW_VALUE_WIDGET_WIDTH);
}