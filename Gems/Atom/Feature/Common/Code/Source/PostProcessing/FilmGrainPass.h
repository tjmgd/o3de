/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <Atom/RPI.Public/Pass/ComputePass.h>

namespace AZ
{
    namespace Render
    {
        class FilmGrainPass final : public RPI::ComputePass
        {
            AZ_RPI_PASS(FilmGrainPass);

        public:
            AZ_RTTI(FilmGrainPass, "{9575D0A9-72AF-47BD-AB4B-544E4C62A7F9}", AZ::RPI::ComputePass);
            AZ_CLASS_ALLOCATOR(FilmGrainPass, SystemAllocator, 0);

            ~FilmGrainPass() = default;
            static RPI::Ptr<FilmGrainPass> Create(const RPI::PassDescriptor& descriptor);

            bool IsEnabled() const override;

        protected:
            // Behavior functions override...
            void FrameBeginInternal(FramePrepareParams params) override;

        private:
            FilmGrainPass(const RPI::PassDescriptor& descriptor);

            AZ::RHI::ShaderInputNameIndex m_constantsIndex = "m_constants";
        };
    } // namespace Render
} // namespace AZ
