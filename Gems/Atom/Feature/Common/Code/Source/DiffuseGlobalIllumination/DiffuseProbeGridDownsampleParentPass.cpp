/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <DiffuseGlobalIllumination/DiffuseProbeGridDownsampleParentPass.h>
#include <DiffuseGlobalIllumination/DiffuseProbeGridFeatureProcessor.h>
#include <RayTracing/RayTracingFeatureProcessor.h>

namespace AZ
{
    namespace Render
    {
        // --- Parent Pass ---

        RPI::Ptr<DiffuseProbeGridDownsampleParentPass> DiffuseProbeGridDownsampleParentPass::Create(const RPI::PassDescriptor& descriptor)
        {
            RPI::Ptr<DiffuseProbeGridDownsampleParentPass> pass = aznew DiffuseProbeGridDownsampleParentPass(descriptor);
            return AZStd::move(pass);
        }

        DiffuseProbeGridDownsampleParentPass::DiffuseProbeGridDownsampleParentPass(const RPI::PassDescriptor& descriptor)
            : RPI::ParentPass(descriptor)
        { }

        bool DiffuseProbeGridDownsampleParentPass::IsEnabled() const
        {
            if (!ParentPass::IsEnabled())
            {
                return false;
            }
            const RPI::Scene* scene = GetScene();
            if (!scene)
            {
                return false;
            }
            return false;
        }
    } // namespace Render
} // namespace AZ
