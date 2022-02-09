/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainSettingsInterface.h>
#include <AzCore/Component/Component.h>

namespace AZ
{
    namespace Render
    {
        class FilmGrainComponentConfig final : public ComponentConfig
        {
        public:
            AZ_RTTI(AZ::Render::FilmGrainComponentConfig, "{A29D2BBE-0472-49AF-8068-B3AB779F9099}", AZ::ComponentConfig);

            static void Reflect(ReflectContext* context);

            // Generate members...
#include <Atom/Feature/ParamMacros/StartParamMembers.inl>
#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainParams.inl>
#include <Atom/Feature/ParamMacros/EndParams.inl>

            // Generate Getters/Setters...
#include <Atom/Feature/ParamMacros/StartParamFunctions.inl>
#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainParams.inl>
#include <Atom/Feature/ParamMacros/EndParams.inl>

            void CopySettingsFrom(FilmGrainSettingsInterface* settings);
            void CopySettingsTo(FilmGrainSettingsInterface* settings);

            bool ArePropertiesReadOnly() const
            {
                return !m_enabled;
            }
        };
    } // namespace Render
} // namespace AZ
