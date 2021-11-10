/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <Atom/RPI.Public/Pass/ParentPass.h>

namespace AZ
{
    namespace Render
    {
        //! A parent pass for DiffuseProbeGridDownsample to allow for disabling
        class DiffuseProbeGridDownsampleParentPass final
            : public RPI::ParentPass
        {
            AZ_RPI_PASS(DiffuseProbeGridDownsampleParentPass);
      
        public:
            AZ_RTTI(DiffuseProbeGridDownsampleParentPass, "{A2B01ADF-078A-4490-BBA6-B50E4CE12C1C}", AZ::RPI::ParentPass);
            AZ_CLASS_ALLOCATOR(DiffuseProbeGridDownsampleParentPass, SystemAllocator, 0);

            ~DiffuseProbeGridDownsampleParentPass() = default;
            static RPI::Ptr<DiffuseProbeGridDownsampleParentPass> Create(const RPI::PassDescriptor& descriptor);

            bool IsEnabled() const override;
        
        private:
            DiffuseProbeGridDownsampleParentPass(const RPI::PassDescriptor& descriptor);

        };
    } // namespace Render
} // namespace AZ
