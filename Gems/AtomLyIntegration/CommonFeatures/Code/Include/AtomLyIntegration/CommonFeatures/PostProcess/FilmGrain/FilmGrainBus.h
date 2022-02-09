/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainConstants.h>
#include <AzCore/Component/Component.h>

namespace AZ
{
    namespace Render
    {
        class FilmGrainRequests : public ComponentBus
        {
        public:
            AZ_RTTI(AZ::Render::FilmGrainRequests, "{D94212E5-9954-4BDA-B38E-05C6B9566862}");

            /// Overrides the default AZ::EBusTraits handler policy to allow one listener only.
            static const EBusHandlerPolicy HandlerPolicy = EBusHandlerPolicy::Single;
            virtual ~FilmGrainRequests()
            {
            }

            // Auto-gen virtual getters/setters...
#include <Atom/Feature/ParamMacros/StartParamFunctionsVirtual.inl>
#include <Atom/Feature/PostProcess/FilmGrain/FilmGrainParams.inl>
#include <Atom/Feature/ParamMacros/EndParams.inl>
        };

        typedef AZ::EBus<FilmGrainRequests> FilmGrainRequestBus;
    } // namespace Render
} // namespace AZ
