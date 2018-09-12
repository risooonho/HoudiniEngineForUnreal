#include "HoudiniApi.h"
#include "HoudiniParameterFactory.h"

#include "HoudiniRuntimeSettings.h"

#include "Parameters/HoudiniAssetParameterString.h"
#include "Parameters/HoudiniAssetParameterChoice.h"
#include "Parameters/HoudiniAssetParameterInt.h"
#include "Parameters/HoudiniAssetParameterFloat.h"
#include "Parameters/HoudiniAssetParameterToggle.h"
#include "Parameters/HoudiniAssetParameterColor.h"
#include "Parameters/HoudiniAssetParameterLabel.h"
#include "Parameters/HoudiniAssetParameterButton.h"
#include "Parameters/HoudiniAssetParameterSeparator.h"
#include "Parameters/HoudiniAssetParameterFolderList.h"
#include "Parameters/HoudiniAssetParameterFolder.h"
#include "Parameters/HoudiniAssetParameterFile.h"
#include "Parameters/HoudiniAssetInput.h"
#include "Parameters/HoudiniAssetParameterRamp.h"

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_STRING>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    if (!ParameterInfo.choiceCount)
        return UHoudiniAssetParameterString::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
    else
        return UHoudiniAssetParameterChoice::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_INT>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    if (!ParameterInfo.choiceCount)
        return UHoudiniAssetParameterInt::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
    else
        return UHoudiniAssetParameterChoice::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_FLOAT>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterFloat::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_TOGGLE>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterToggle::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_COLOR>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterColor::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_LABEL>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterLabel::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_BUTTON>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterButton::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_SEPARATOR>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterSeparator::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_FOLDERLIST>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterFolderList::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_FOLDER>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterFolder::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_MULTIPARMLIST>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    bool bTreatRampParametersAsMultiparms = false;
    const auto HoudiniRuntimeSettings = GetDefault<UHoudiniRuntimeSettings>();
    if (HoudiniRuntimeSettings)
        bTreatRampParametersAsMultiparms = HoudiniRuntimeSettings->bTreatRampParametersAsMultiparms;

    if (!bTreatRampParametersAsMultiparms && (HAPI_RAMPTYPE_FLOAT == ParameterInfo.rampType || HAPI_RAMPTYPE_COLOR == ParameterInfo.rampType))
        return UHoudiniAssetParameterRamp::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
    else
        return UHoudiniAssetParameterMultiparm::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_PATH_FILE_IMAGE>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return UHoudiniAssetParameterFile::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_PATH_FILE>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return Create<HAPI_PARMTYPE_PATH_FILE_IMAGE>(PrimaryObject, ParentParameter, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_PATH_FILE_GEO>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    return Create<HAPI_PARMTYPE_PATH_FILE_IMAGE>(PrimaryObject, ParentParameter, NodeId, ParameterInfo);
}

template <>
UHoudiniAssetParameter* FHoudiniParameterFactory::Create<HAPI_PARMTYPE_NODE>(UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    if (ParameterInfo.inputNodeType == HAPI_NODETYPE_ANY 
        || ParameterInfo.inputNodeType == HAPI_NODETYPE_SOP 
        || ParameterInfo.inputNodeType == HAPI_NODETYPE_OBJ)
        return UHoudiniAssetInput::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
    else
        return UHoudiniAssetParameterString::Create(PrimaryObject, nullptr, NodeId, ParameterInfo);
}

TMap<HAPI_ParmType, FHoudiniParameterFactory::FHoudiniParameterFactoryFunc> FHoudiniParameterFactory::Factories;
UHoudiniAssetParameter* FHoudiniParameterFactory::Create(HAPI_ParmType ParameterType, UObject* PrimaryObject, UHoudiniAssetParameter* ParentParameter, HAPI_NodeId NodeId, const HAPI_ParmInfo& ParameterInfo)
{
    if (Factories.Num() == 0)
    {
        Factories.Add(HAPI_PARMTYPE_STRING, Create<HAPI_PARMTYPE_STRING>);
        Factories.Add(HAPI_PARMTYPE_INT, Create<HAPI_PARMTYPE_INT>);
        Factories.Add(HAPI_PARMTYPE_FLOAT, Create<HAPI_PARMTYPE_FLOAT>);
        Factories.Add(HAPI_PARMTYPE_TOGGLE, Create<HAPI_PARMTYPE_TOGGLE>);
        Factories.Add(HAPI_PARMTYPE_COLOR, Create<HAPI_PARMTYPE_COLOR>);
        Factories.Add(HAPI_PARMTYPE_LABEL, Create<HAPI_PARMTYPE_LABEL>);
        Factories.Add(HAPI_PARMTYPE_BUTTON, Create<HAPI_PARMTYPE_BUTTON>);
        Factories.Add(HAPI_PARMTYPE_SEPARATOR, Create<HAPI_PARMTYPE_SEPARATOR>);
        Factories.Add(HAPI_PARMTYPE_FOLDERLIST, Create<HAPI_PARMTYPE_FOLDERLIST>);
        Factories.Add(HAPI_PARMTYPE_FOLDER, Create<HAPI_PARMTYPE_FOLDER>);
        Factories.Add(HAPI_PARMTYPE_MULTIPARMLIST, Create<HAPI_PARMTYPE_MULTIPARMLIST>);
        Factories.Add(HAPI_PARMTYPE_PATH_FILE_IMAGE, Create<HAPI_PARMTYPE_PATH_FILE_IMAGE>);
        Factories.Add(HAPI_PARMTYPE_PATH_FILE, Create<HAPI_PARMTYPE_PATH_FILE>);
        Factories.Add(HAPI_PARMTYPE_PATH_FILE_GEO, Create<HAPI_PARMTYPE_PATH_FILE_GEO>);
        Factories.Add(HAPI_PARMTYPE_NODE, Create<HAPI_PARMTYPE_NODE>);
    }

    auto Factory = Factories[ParameterType];
    ensure(Factory);

    return Factory(PrimaryObject, ParentParameter, NodeId, ParameterInfo);
}

TMap<HAPI_ParmType, FHoudiniParameterFactory::FHoudiniParameterTypeCheckFunc> FHoudiniParameterFactory::TypeCheckers;
bool FHoudiniParameterFactory::CheckType(HAPI_ParmType ParameterType, UClass* Class)
{
    if (TypeCheckers.Num() == 0)
    {
        TypeCheckers.Add(HAPI_PARMTYPE_STRING, CheckType<HAPI_PARMTYPE_STRING>);
    }

    auto TypeChecker = TypeCheckers[ParameterType];
    ensure(TypeChecker);

    return TypeChecker(Class);
}