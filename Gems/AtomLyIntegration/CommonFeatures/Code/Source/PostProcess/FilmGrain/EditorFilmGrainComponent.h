/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <Atom/Feature/PostProcess/DepthOfField/DepthOfFieldConstants.h>
#include <AzToolsFramework/ToolsComponents/EditorComponentAdapter.h>
#include <PostProcess/FilmGrain/FilmGrainComponent.h>

namespace AZ
{
    namespace Render
    {
        namespace FilmGrain
        {
            static constexpr const char* const EditorFilmGrainComponentTypeId = "{4D16E2A4-3F49-40FC-9667-D24B272CADFA}";
        }

        class EditorFilmGrainComponent final
            : public AzToolsFramework::Components::
                  EditorComponentAdapter<FilmGrainComponentController, FilmGrainComponent, FilmGrainComponentConfig>
        {
        public:
            using BaseClass = AzToolsFramework::Components::
                EditorComponentAdapter<FilmGrainComponentController, FilmGrainComponent, FilmGrainComponentConfig>;
            AZ_EDITOR_COMPONENT(AZ::Render::EditorFilmGrainComponent, FilmGrain::EditorFilmGrainComponentTypeId, BaseClass);

            static void Reflect(AZ::ReflectContext* context);

            EditorFilmGrainComponent() = default;
            EditorFilmGrainComponent(const FilmGrainComponentConfig& config);

            //! EditorRenderComponentAdapter overrides...
            AZ::u32 OnConfigurationChanged() override;
        };

    } // namespace Render
} // namespace AZ
