/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <PostProcessing/FilmGrainPass.h>
#include <PostProcess/PostProcessFeatureProcessor.h>
#include <Atom/RPI.Public/RenderPipeline.h>
#include <Atom/RPI.Public/Scene.h>

namespace AZ
{
    namespace Render
    {
        RPI::Ptr<FilmGrainPass> FilmGrainPass::Create(const RPI::PassDescriptor& descriptor)
        {
            RPI::Ptr<FilmGrainPass> pass = aznew FilmGrainPass(descriptor);
            return AZStd::move(pass);
        }

        FilmGrainPass::FilmGrainPass(const RPI::PassDescriptor& descriptor)
            : RPI::ComputePass(descriptor)
        {
        }

        bool FilmGrainPass::IsEnabled() const
        {
            if (!ComputePass::IsEnabled())
            {
                return false;
            }
            const RPI::Scene* scene = GetScene();
            if (!scene)
            {
                return false;
            }
            PostProcessFeatureProcessor* fp = scene->GetFeatureProcessor<PostProcessFeatureProcessor>();
            const RPI::ViewPtr view = GetRenderPipeline()->GetDefaultView();
            if (!fp)
            {
                return true;
            }
            PostProcessSettings* postProcessSettings = fp->GetLevelSettingsFromView(view);
            if (!postProcessSettings)
            {
                return true;
            }
            const FilmGrainSettings* filmGrainSettings = postProcessSettings->GetFilmGrainSettings();
            if (!filmGrainSettings)
            {
                return true;
            }
            return (filmGrainSettings != nullptr) && filmGrainSettings->GetEnabled();
        }

        /* void FilmGrainPass::UpdateParameters()
        {
            auto UpdateIfChanged = [](float& local, float input) -> bool
            {
                if (local != input)
                {
                    local = input;
                    return true;
                }
                else
                {
                    return false;
                }
            };

            RPI::Scene* scene = GetScene();
            PostProcessFeatureProcessor* fp = scene->GetFeatureProcessor<PostProcessFeatureProcessor>();
            RPI::ViewPtr view = scene->GetDefaultRenderPipeline()->GetDefaultView();
            if (fp)
            {
                PostProcessSettings* postProcessSettings = fp->GetLevelSettingsFromView(view);
                if (postProcessSettings)
                {
                    FilmGrainSettings* filmGrainSettings = postProcessSettings->GetFilmGrainSettings();
                    if (filmGrainSettings)
                    {
                        m_paramsUpdated |= UpdateIfChanged(m_grain, filmGrainSettings->GetGrain());
                    }
                }
            }
        }*/

        Data::Instance<RPI::Image> FilmGrainPass::GetFilmGrainImage() // temp
        {
            RPI::Scene* scene = GetScene();
            PostProcessFeatureProcessor* fp = scene->GetFeatureProcessor<PostProcessFeatureProcessor>();
            RPI::ViewPtr view = scene->GetDefaultRenderPipeline()->GetDefaultView();
            fp->GetFilmGrain();
        }

        void FilmGrainPass::FrameBeginInternal(FramePrepareParams params)
        {
            Data::Instance<RPI::Image> grainImage = GetFilmGrainImage();
            m_shaderResourceGroup->SetImage(m_grainIndex, grainImage);

            // Must match the struct in .azsl
            struct Constants
            {
                AZStd::array<u32, 2> m_outputSize;
                float m_strength;
                float m_luminanceDampening;
            } constants{};

            AZ_Assert(GetOutputCount() > 0, "FilmGrainPass: No output bindings!");
            RPI::PassAttachment* outputAttachment = GetOutputBinding(0).m_attachment.get();

            AZ_Assert(outputAttachment != nullptr, "FilmGrainPass: Output binding has no attachment!");
            RHI::Size size = outputAttachment->m_descriptor.m_image.m_size;

            constants.m_outputSize[0] = size.m_width;
            constants.m_outputSize[1] = size.m_height;
            //constants.m_strength = ;
            //constants.m_luminanceDampening = ;

            m_shaderResourceGroup->SetConstant(m_constantsIndex, constants);

            RPI::ComputePass::FrameBeginInternal(params);
        }

    } // namespace Render
} // namespace AZ
