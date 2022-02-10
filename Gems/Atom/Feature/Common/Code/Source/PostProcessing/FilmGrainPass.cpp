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

        void FilmGrainPass::FrameBeginInternal(FramePrepareParams params)
        {
            // Must match the struct in .azsl
            struct Constants
            {
                AZStd::array<u32, 2> m_outputSize;
                float m_strength;
            } constants{};

            AZ_Assert(GetOutputCount() > 0, "FilmGrainPass: No output bindings!");
            RPI::PassAttachment* outputAttachment = GetOutputBinding(0).m_attachment.get();

            AZ_Assert(outputAttachment != nullptr, "FilmGrainPass: Output binding has no attachment!");
            RHI::Size size = outputAttachment->m_descriptor.m_image.m_size;

            constants.m_outputSize[0] = size.m_width;
            constants.m_outputSize[1] = size.m_height;
            constants.m_strength = 0.5f;

            /*      
                    propertyIndex = material->FindPropertyIndex(AZ::Name("baseColor.textureMap"));
                    if (propertyIndex.IsValid())
                    {
                        Data::Instance<RPI::Image> image = material->GetPropertyValue<Data::Instance<RPI::Image>>(propertyIndex);
                        if (image.get())
                        {
                            subMesh.m_textureFlags |= RayTracingSubMeshTextureFlags::BaseColor;
                            subMesh.m_baseColorImageView = image->GetImageView();
                        }
                    }
            */

            m_shaderResourceGroup->SetConstant(m_constantsIndex, constants);

            RPI::ComputePass::FrameBeginInternal(params);
        }

    } // namespace Render
} // namespace AZ
