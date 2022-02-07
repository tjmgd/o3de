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
            return true;
        }

        void FilmGrainPass::FrameBeginInternal(FramePrepareParams params)
        {
            // Must match the struct in .azsl
            struct Constants
            {
                AZStd::array<u32, 2> m_outputSize;
                float m_strength;
            } constants{};

            // FUTURE PROOFING WIP
            /* RPI::Scene* scene = GetScene();
            PostProcessFeatureProcessor* fp = scene->GetFeatureProcessor<PostProcessFeatureProcessor>();
            AZ::RPI::ViewPtr view = scene->GetDefaultRenderPipeline()->GetDefaultView();
            if (fp)
            {
                PostProcessSettings* postProcessSettings = fp->GetLevelSettingsFromView(view);
                if (postProcessSettings)
                {
                    ChromaticAbberationSettings* settings = postProcessSettings->GetChromaticAbberationSettings();
                    if (settings)
                    {
                        if (settings->GetEnabled())
                        {
                            constants.m_strength = settings->GetStrength();
                            //etc
                        }
                        else
                        {
                            constants.m_strength = 0.0f;
                            //etc
                        }
                    }
                }
            }*/

            AZ_Assert(GetOutputCount() > 0, "FilmGrainPass: No output bindings!");
            RPI::PassAttachment* outputAttachment = GetOutputBinding(0).m_attachment.get();

            AZ_Assert(outputAttachment != nullptr, "FilmGrainPass: Output binding has no attachment!");
            RHI::Size size = outputAttachment->m_descriptor.m_image.m_size;

            constants.m_outputSize[0] = size.m_width;
            constants.m_outputSize[1] = size.m_height;
            constants.m_strength = 0.5f;

            m_shaderResourceGroup->SetConstant(m_constantsIndex, constants);

            RPI::ComputePass::FrameBeginInternal(params);
        }

    } // namespace Render
} // namespace AZ
