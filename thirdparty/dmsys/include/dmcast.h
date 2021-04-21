
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
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

#ifndef __DMCAST_H_INCLUDE__
#define __DMCAST_H_INCLUDE__

#include <string>

namespace dmcast
{

template <typename To, typename From>
struct Converter
{
    static To convert(const From& from)
    {
        return To();
    }
};

template <typename From>
struct Converter<char, From>
{
    static char convert(const From& from)
    {
        return std::stoi(from);
    }
};

template <typename From>
struct Converter<int8_t, From>
{
    static int8_t convert(const From& from)
    {
        return std::stoi(from);
    }
};

template <typename From>
struct Converter<uint8_t, From>
{
    static uint8_t convert(const From& from)
    {
        return std::stoul(from);
    }
};

template <typename From>
struct Converter<int16_t, From>
{
    static int16_t convert(const From& from)
    {
        return std::stoi(from);
    }
};

template <typename From>
struct Converter<uint16_t, From>
{
    static uint16_t convert(const From& from)
    {
        return std::stoul(from);
    }
};

template <typename From>
struct Converter<int32_t, From>
{
    static int32_t convert(const From& from)
    {
        return std::stoi(from);
    }
};

template <typename From>
struct Converter<uint32_t, From>
{
    static uint32_t convert(const From& from)
    {
        return std::stoul(from);
    }
};

template <typename From>
struct Converter<int64_t, From>
{
    static int64_t convert(const From& from)
    {
        return std::stoll(from);
    }
};

template <typename From>
struct Converter<uint64_t, From>
{
    static uint64_t convert(const From& from)
    {
        return std::stoull(from);
    }
};

template <typename From>
struct Converter<float, From>
{
    static float convert(const From& from)
    {
        return std::stof(from);
    }
};

template <typename From>
struct Converter<double, From>
{
    static double convert(const From& from)
    {
        return std::stod(from);
    }
};

template <typename From>
struct Converter<long double, From>
{
    static long double convert(const From& from)
    {
        return std::stold(from);
    }
};

template <typename From>
struct Converter<bool, From>
{
    static typename std::enable_if<std::is_integral<From>::value, bool>::type
    convert(From from)
    {
        return !!from;
    }
};

template <>
struct Converter<bool, std::string>
{
    static bool convert(const std::string& from)
    {
        return !!std::stoi(from);
    }
};

template <>
struct Converter<bool, const char*>
{
    static bool convert(const char* from)
    {
        return !!std::stoi(from);
    }
};

template <>
struct Converter<bool, char*>
{
    static bool convert(char* from)
    {
        return !!std::stoi(from);
    }
};

template <unsigned N>
struct Converter<bool, const char[N]>
{
    static bool convert(const char(&from)[N])
    {
        return !!std::stoi(from);
    }
};

template <unsigned N>
struct Converter<bool, char[N]>
{
    static bool convert(const char(&from)[N])
    {
        return !!std::stoi(from);
    }
};

template <typename From>
struct Converter<std::string, From>
{
    static std::string convert(const From& from)
    {
        return std::to_string(from);
    }
};

template <>
struct Converter<std::string, bool>
{
    static std::string convert(const bool& from)
    {
        return std::to_string((int)from);
    }
};

template <>
struct Converter<std::string, const char*>
{
    static std::string convert(const char* from)
    {
        return from;
    }
};

template <unsigned N>
struct Converter<std::string, char[N]>
{
    static std::string convert(const char(&from)[N])
    {
        return from;
    }
};

template <typename To, typename From>
typename std::enable_if<!std::is_same<To, From>::value,
         To>::type lexical_cast(const From& from)
{
    return dmcast::Converter<To, From>::convert(from);
}

template <typename To, typename From>
typename std::enable_if<std::is_same<To, From>::value, To>::type lexical_cast(
    const From& from)
{
    return from;
}

// #include <tuple>

//template <typename ... T>
//std::string lexical_cast(std::tuple<T...>& t)
//{
//    std::string strData;
//    std::apply([&](auto&& ... args)
//    {
//        ((strData += (strData.empty() ? "" : ","),
//          strData += lexical_cast<std::string>(args)), ...);
//    }, t);
//    return strData;
//}

}
#endif // __DMCAST_H_INCLUDE__

