// Altered SFML BlendMode.hpp for Ancona's namespace

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef Ancona_HAL_BlendMode_H_
#define Ancona_HAL_BlendMode_H_

namespace ildhal
{

struct BlendMode
{
    ////////////////////////////////////////////////////////
    /// \brief Enumeration of the blending factors
    ///
    /// The factors are mapped directly to their OpenGL equivalents,
    /// specified by glBlendFunc() or glBlendFuncSeparate().
    ////////////////////////////////////////////////////////
    enum Factor
    {
        Zero,             ///< (0, 0, 0, 0)
        One,              ///< (1, 1, 1, 1)
        SrcColor,         ///< (src.r, src.g, src.b, src.a)
        OneMinusSrcColor, ///< (1, 1, 1, 1) - (src.r, src.g, src.b, src.a)
        DstColor,         ///< (dst.r, dst.g, dst.b, dst.a)
        OneMinusDstColor, ///< (1, 1, 1, 1) - (dst.r, dst.g, dst.b, dst.a)
        SrcAlpha,         ///< (src.a, src.a, src.a, src.a)
        OneMinusSrcAlpha, ///< (1, 1, 1, 1) - (src.a, src.a, src.a, src.a)
        DstAlpha,         ///< (dst.a, dst.a, dst.a, dst.a)
        OneMinusDstAlpha  ///< (1, 1, 1, 1) - (dst.a, dst.a, dst.a, dst.a)
    };

    ////////////////////////////////////////////////////////
    /// \brief Enumeration of the blending equations
    ///
    /// The equations are mapped directly to their OpenGL equivalents,
    /// specified by glBlendEquation() or glBlendEquationSeparate().
    ////////////////////////////////////////////////////////
    enum Equation
    {
        Add,            ///< Pixel = Src * SrcFactor + Dst * DstFactor
        Subtract,       ///< Pixel = Src * SrcFactor - Dst * DstFactor
        ReverseSubtract ///< Pixel = Dst * DstFactor - Src * SrcFactor
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructs a blending mode that does alpha blending.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the blend mode given the factors and equation.
    ///
    /// This constructor uses the same factors and equation for both
    /// color and alpha components. It also defaults to the Add equation.
    ///
    /// \param sourceFactor      Specifies how to compute the source factor for the color and alpha channels.
    /// \param destinationFactor Specifies how to compute the destination factor for the color and alpha channels.
    /// \param blendEquation     Specifies how to combine the source and destination colors and alpha.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode(Factor sourceFactor, Factor destinationFactor, Equation blendEquation = Add);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the blend mode given the factors and equation.
    ///
    /// \param colorSourceFactor      Specifies how to compute the source factor for the color channels.
    /// \param colorDestinationFactor Specifies how to compute the destination factor for the color channels.
    /// \param colorBlendEquation     Specifies how to combine the source and destination colors.
    /// \param alphaSourceFactor      Specifies how to compute the source factor.
    /// \param alphaDestinationFactor Specifies how to compute the destination factor.
    /// \param alphaBlendEquation     Specifies how to combine the source and destination alphas.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode(Factor colorSourceFactor, Factor colorDestinationFactor, Equation colorBlendEquation,
              Factor alphaSourceFactor, Factor alphaDestinationFactor, Equation alphaBlendEquation);

    ////////////////////////////////////////////////////////////
    // Member Data
    ////////////////////////////////////////////////////////////
    Factor colorSrcFactor;  ///< Source blending factor for the color channels
    Factor colorDstFactor;  ///< Destination blending factor for the color channels
    Equation colorEquation; ///< Blending equation for the color channels
    Factor alphaSrcFactor;  ///< Source blending factor for the alpha channel
    Factor alphaDstFactor;  ///< Destination blending factor for the alpha channel
    Equation alphaEquation; ///< Blending equation for the alpha channel
};

bool operator==(const BlendMode &left, const BlendMode &right);
bool operator!=(const BlendMode &left, const BlendMode &right);

////////////////////////////////////////////////////////////
// Commonly used blending modes
////////////////////////////////////////////////////////////
extern const BlendMode BlendAlpha;    ///< Blend source and dest according to dest alpha
extern const BlendMode BlendAdd;      ///< Add source to dest
extern const BlendMode BlendMultiply; ///< Multiply source and dest
extern const BlendMode BlendNone;     ///< Overwrite dest with source

} // namespace ildhal

#endif
