/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TransformBus.h>

#include <AtomLyIntegration/CommonFeatures/PostProcess/FilmGrain/FilmGrainBus.h>
#include <AtomLyIntegration/CommonFeatures/PostProcess/FilmGrain/FilmGrainComponentConfig.h>

#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainConstants.h>
#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainSettingsInterface.h>
#include <Atom/Feature/PostProcess/PostProcessFeatureProcessorInterface.h>
#include <Atom/Feature/PostProcess/PostProcessSettingsInterface.h>

namespace AZ
{
    namespace Render
    {
        class FilmGrainComponentController final : public FilmGrainRequestBus::Handler
        {
        public:
            friend class EditorFilmGrainComponent;

            AZ_TYPE_INFO(AZ::Render::FilmGrainComponentController, "{709B8FAA-E78F-404F-AD21-55E6A92400AD}");
            static void Reflect(AZ::ReflectContext* context);
            static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
            static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
            static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);

            FilmGrainComponentController() = default;
            FilmGrainComponentController(const FilmGrainComponentConfig& config);

            void Activate(EntityId entityId);
            void Deactivate();
            void SetConfiguration(const FilmGrainComponentConfig& config);
            const FilmGrainComponentConfig& GetConfiguration() const;

            // Auto-gen function override declarations (functions definitions in .cpp)...
#include <Atom/Feature/ParamMacros/StartParamFunctionsOverride.inl>
#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainParams.inl>
#include <Atom/Feature/ParamMacros/EndParams.inl>

        private:
            AZ_DISABLE_COPY(FilmGrainComponentController);

            void OnConfigChanged();

            PostProcessSettingsInterface* m_postProcessInterface = nullptr;
            FilmGrainSettingsInterface* m_settingsInterface = nullptr;
            FilmGrainComponentConfig m_configuration;
            EntityId m_entityId;
        };
    } // namespace Render
} // namespace AZ
