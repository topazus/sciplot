// sciplot - a modern C++ scientific plotting library powered by gnuplot
// https://github.com/sciplot/sciplot
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018 Allan Leal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// sciplot includes
#include <sciplot/default.hpp>
#include <sciplot/specs/FontSpecs.hpp>
#include <sciplot/util.hpp>

namespace sciplot
{

/// The class used to specify options for text elements.
template <typename DerivedSpecs>
class TextSpecs : public FontSpecs<DerivedSpecs>
{
  public:
    /// Construct a default TextSpecs instance.
    TextSpecs();

    /// Set the enhanced mode of the text.
    /// The enhanced text mode allows superscript text to be represented as
    /// `a^x`, subscript text with `a_x`, and combined superscript and
    /// subscript text with `a@^b_{cd}`.
    /// For more details, read "Enhanced text mode" section of the Gnuplot manual.
    auto enhanced(bool value=true) -> DerivedSpecs&;

    /// Set the color of the text (e.g., `"blue"`, `"#404040"`)
    auto textColor(std::string color) -> DerivedSpecs&;

    /// Convert this TextSpecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

  private:
    /// The color of the title text.
    std::string m_color;

    /// The enhanced mode of the text (enhanced or noenhanced)
    std::string m_enhanced;
};

template <typename DerivedSpecs>
TextSpecs<DerivedSpecs>::TextSpecs()
{
    enhanced(true);
    textColor(internal::DEFAULT_TEXTCOLOR);
}

template <typename DerivedSpecs>
auto TextSpecs<DerivedSpecs>::enhanced(bool value) -> DerivedSpecs&
{
    m_enhanced = value ? "enhanced" : "noenhanced";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TextSpecs<DerivedSpecs>::textColor(std::string color) -> DerivedSpecs&
{
    m_color = "'" + color + "'";
    return static_cast<DerivedSpecs&>(*this);
}

template <typename DerivedSpecs>
auto TextSpecs<DerivedSpecs>::repr() const -> std::string
{
    std::stringstream ss;
    ss << m_enhanced << " textcolor " << m_color << " ";
    ss << FontSpecs<DerivedSpecs>::repr();
    return internal::removeExtraWhitespaces(ss.str());
}

} // namespace sciplot
