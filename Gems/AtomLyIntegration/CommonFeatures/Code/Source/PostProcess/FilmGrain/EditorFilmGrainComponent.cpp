/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/RTTI/BehaviorContext.h>
#include <PostProcess/FilmGrain/EditorFilmGrainComponent.h>

namespace AZ
{
    namespace Render
    {
        void EditorFilmGrainComponent::Reflect(AZ::ReflectContext* context)
        {
            BaseClass::Reflect(context);

            if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<EditorFilmGrainComponent, BaseClass>()->Version(1);

                if (AZ::EditContext* editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<EditorFilmGrainComponent>("Film Grain", "Controls the Film Grain")
                        ->ClassElement(Edit::ClassElements::EditorData, "")
                        ->Attribute(Edit::Attributes::Category, "Atom")
                        ->Attribute(
                            AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg") // [GFX TODO ATOM-2672][PostFX] need
                                                                                                      // to create icons for PostProcessing.
                        ->Attribute(
                            AZ::Edit::Attributes::ViewportIcon,
                            "Icons/Components/Viewport/Component_Placeholder.svg") // [GFX TODO ATOM-2672][PostFX] need to create icons for
                                                                                   // PostProcessing.
                        ->Attribute(Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("Game", 0x232b318c))
                        ->Attribute(Edit::Attributes::AutoExpand, true)
                        ->Attribute(
                            Edit::Attributes::HelpPageURL,
                            "https://o3de.org/docs/user-guide/components/reference/atom/filmgrain/") // [TODO ATOM-2672][PostFX] need create
                                                                                                 // page for PostProcessing.
                        ;

                    editContext->Class<FilmGrainComponentController>("ExposureControlComponentController", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &FilmGrainComponentController::m_configuration, "Configuration", "")
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly);

                    editContext->Class<FilmGrainComponentConfig>("FilmGrainComponentConfig", "")
                        ->DataElement(Edit::UIHandlers::CheckBox, &FilmGrainComponentConfig::m_enabled, "Enable Bloom", "Enable Bloom.")
                        ->Attribute(Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Default, &FilmGrainComponentConfig::m_threshold, "Threshold",
                            "How bright is the light source bloom applied to ")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_knee, "Knee",
                            "Soft knee to smoothen edge of threshold")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_intensity, "Intensity", "Brightness of bloom")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 10000.0f)
                        ->Attribute(AZ::Edit::Attributes::SoftMax, 25.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::CheckBox, &FilmGrainComponentConfig::m_enableBicubic, "Enable Bicubic",
                            "Enable bicubic filter for upsampling")
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        // Kernel sizes
                        ->ClassElement(AZ::Edit::ClassElements::Group, "Kernel Size")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, false)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_kernelSizeScale, "Kernel Size Scale",
                            "Global scaling factor of kernel size")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 2.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_kernelSizeStage0, "Kernel Size 0",
                            "Kernel size for blur stage 0 in percent of screen width")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_kernelSizeStage1, "Kernel Size 1",
                            "Kernel size for blur stage 1 in percent of screen width")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_kernelSizeStage2, "Kernel Size 2",
                            "Kernel size for blur stage 2 in percent of screen width")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_kernelSizeStage3, "Kernel Size 3",
                            "Kernel size for blur stage 3 in percent of screen width")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Slider, &FilmGrainComponentConfig::m_kernelSizeStage4, "Kernel Size 4",
                            "Kernel size for blur stage 4 in percent of screen width")
                        ->Attribute(AZ::Edit::Attributes::Min, 0.0f)
                        ->Attribute(AZ::Edit::Attributes::Max, 1.0f)
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        // Tints
                        ->ClassElement(AZ::Edit::ClassElements::Group, "Tint")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, false)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Color, &FilmGrainComponentConfig::m_tintStage0, "Tint 0", "Tint for blur stage 0")
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Color, &FilmGrainComponentConfig::m_tintStage1, "Tint 1", "Tint for blur stage 1")
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Color, &FilmGrainComponentConfig::m_tintStage2, "Tint 2", "Tint for blur stage 2")
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Color, &FilmGrainComponentConfig::m_tintStage3, "Tint 3", "Tint for blur stage 3")
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        ->DataElement(
                            AZ::Edit::UIHandlers::Color, &FilmGrainComponentConfig::m_tintStage4, "Tint 4", "Tint for blur stage 4")
                        ->Attribute(AZ::Edit::Attributes::ChangeNotify, Edit::PropertyRefreshLevels::ValuesOnly)
                        ->Attribute(Edit::Attributes::ReadOnly, &FilmGrainComponentConfig::ArePropertiesReadOnly)

                        // Overrides
                        ->ClassElement(AZ::Edit::ClassElements::Group, "Overrides")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, false)
                    // Auto-gen editor context settings for overrides
#define EDITOR_CLASS FilmGrainComponentConfig
#include <Atom/Feature/ParamMacros/StartOverrideEditorContext.inl>
#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainParams.inl>
#include <Atom/Feature/ParamMacros/EndParams.inl>
#undef EDITOR_CLASS
                        ;
                }
            }

            if (auto behaviorContext = azrtti_cast<BehaviorContext*>(context))
            {
                behaviorContext->Class<EditorFilmGrainComponent>()->RequestBus("FilmGrainRequestBus");

                behaviorContext
                    ->ConstantProperty("EditorFilmGrainComponentTypeId", BehaviorConstant(Uuid(FilmGrain::EditorFilmGrainComponentTypeId)))
                    ->Attribute(AZ::Script::Attributes::Module, "render")
                    ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Automation);
            }
        }

        EditorFilmGrainComponent::EditorFilmGrainComponent(const FilmGrainComponentConfig& config)
            : BaseClass(config)
        {
        }

        u32 EditorFilmGrainComponent::OnConfigurationChanged()
        {
            m_controller.OnConfigChanged();
            return Edit::PropertyRefreshLevels::AttributesAndValues;
        }
    } // namespace Render
} // namespace AZ
