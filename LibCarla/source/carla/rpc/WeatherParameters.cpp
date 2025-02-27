// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "carla/rpc/WeatherParameters.h"

// 定义在carla和rpc命名空间内，这是一种常见的C++代码组织方式，用于避免命名冲突
namespace carla {
namespace rpc {

  // 使用类型别名WP来指代WeatherParameters类型，方便后续代码书写，使代码更简洁
  using WP = WeatherParameters;

  // 定义WeatherParameters类型的一系列静态成员变量，表示不同天气状况下的默认参数设置。
  // 每个参数的含义大致如下（具体需参照WeatherParameters结构体的定义，这里从变量名推测）：
  // cloudiness：云量（取值范围可能是0 - 100之类的，表示天空被云覆盖的程度，-1可能表示未设置或使用默认计算等情况）
  // precip.：降水量（可能是0 - 100之类表示降水强度，-1同样可能表示未设置等情况）
  // prec.dep.：降水深度（具体含义和单位要看实际应用场景，-1表示未设置等）
  // wind：风速（具体单位不确定，-1表示未设置等）
  // azimuth：风向角度（以某个方向为基准的角度值，-1表示未设置等）
  // altitude：太阳或月亮等天体的高度角（用于区分白天、夜晚、黄昏等不同时段下的光照等情况，-1表示未设置等）
  // fog dens：雾的密度（表示雾的浓厚程度，-1表示未设置等）
  // fog dist：雾的距离（可能是能见度相关的距离参数，-1表示未设置等）
  // fog fall：雾的沉降速度（具体单位和含义要看实际情况，-1表示未设置等）
  // wetness：地面湿度（可能是0 - 100之类表示地面潮湿程度，-1表示未设置等）
  // scat.i：散射强度（可能与光线在大气中的散射情况相关，具体要看实际物理模型定义，0.03表示默认值等情况）
  // mie.scat.s：米氏散射尺度（与大气中粒子对光的散射特性相关的参数，0.0331表示默认值等情况）
  // rayleigh.scat.scale：瑞利散射尺度（同样是和光散射相关参数，0.0表示默认值等情况）
  // dust storm：沙尘强度（可能表示沙尘天气的强度情况，100.0表示沙尘风暴的强度，0.0表示无沙尘等情况）

  // 默认天气参数设置，各个参数大多为 -1，表示未明确指定，可能后续会根据其他逻辑来确定具体值，
  // 最后几个散射相关参数有默认的固定值，具体含义如上述参数说明
  WP WP::Default = {    -1.0f,   -1.0f,    -1.0f,   -1.00f,    -1.0f,     -1.0f,    -1.0f,     -1.0f,    -1.0f,   -1.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 晴朗中午的天气参数设置，云量较少，无降水等，风速、太阳高度角等有对应值，雾相关参数也有相应设定
  WP WP::ClearNoon = {     5.0f,    0.0f,     0.0f,    10.0f,    -1.0f,     45.0f,     2.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 多云中午的天气参数设置，云量较多，无降水，其他参数类似晴朗中午有对应合理值
  WP WP::CloudyNoon = {    60.0f,    0.0f,     0.0f,    10.0f,    -1.0f,     45.0f,     3.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 潮湿但无雨的中午天气参数设置，降水深度有值表示地面是湿的，其他参数与晴天或多云中午类似配合
  WP WP::WetNoon = {     5.0f,    0.0f,    50.0f,    10.0f,    -1.0f,     45.0f,     3.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 潮湿且多云的中午天气参数设置，结合了潮湿和多云的特点，各参数相应设置
  WP WP::WetCloudyNoon = {    60.0f,    0.0f,    50.0f,    10.0f,    -1.0f,     45.0f,     3.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 中雨的中午天气参数设置，降水相关参数都有较高的值表示中雨强度，其他参数配合调整
  WP WP::MidRainyNoon = {    60.0f,   60.0f,    60.0f,    60.0f,    -1.0f,     45.0f,     3.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 大雨的中午天气参数设置，降水相关参数值更高，表示大雨强度，雾等参数也相应变化
  WP WP::HardRainNoon = {   100.0f,  100.0f,    90.0f,    100.0f,   -1.0f,     45.0f,     7.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 小雨的中午天气参数设置，降水相关参数有一定值表示小雨强度，其他参数合理设置
  WP WP::SoftRainNoon = {    20.0f,   30.0f,    50.0f,    30.0f,    -1.0f,     45.0f,     3.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 晴朗日落时的天气参数设置，太阳高度角等参数符合日落时段特点，其他参数相应配合
  WP WP::ClearSunset = {     5.0f,    0.0f,     0.0f,    10.0f,    -1.0f,     15.0f,     2.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 多云日落时的天气参数设置，云量较多，符合日落时多云天气情况，其他参数合理设定
  WP WP::CloudySunset = {    60.0f,    0.0f,     0.0f,    10.0f,    -1.0f,     15.0f,     3.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 潮湿日落时的天气参数设置，地面有一定湿度，其他参数配合日落时段情况
  WP WP::WetSunset = {     5.0f,    0.0f,    50.0f,    10.0f,    -1.0f,     15.0f,     2.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 潮湿且多云日落时的天气参数设置，结合潮湿和多云特点，适配日落时段的各参数设置
  WP WP::WetCloudySunset = {    60.0f,    0.0f,    50.0f,    10.0f,    -1.0f,     15.0f,     2.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 中雨日落时的天气参数设置，降水相关参数体现中雨强度，配合日落时段其他参数
  WP WP::MidRainSunset = {    60.0f,   60.0f,    60.0f,    60.0f,    -1.0f,     15.0f,     3.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 大雨日落时的天气参数设置，降水强度大，各参数适配大雨日落的情况
  WP WP::HardRainSunset = {   100.0f,  100.0f,    90.0f,    100.0f,   -1.0f,     15.0f,     7.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 小雨日落时的天气参数设置，体现小雨强度，配合日落时的其他环境参数
  WP WP::SoftRainSunset = {    20.0f,   30.0f,    50.0f,    30.0f,    -1.0f,     15.0f,     2.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 晴朗夜晚的天气参数设置，太阳高度角为负表示夜晚，雾等参数有相应的夜晚特点设置
  WP WP::ClearNight = {     5.0f,    0.0f,     0.0f,    10.0f,    -1.0f,    -90.0f,    60.0f,     75.0f,     1.0f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 多云夜晚的天气参数设置，云量较多，符合夜晚多云天气情况，其他参数相应调整
  WP WP::CloudyNight = {    60.0f,    0.0f,     0.0f,    10.0f,    -1.0f,    -90.0f,    60.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 潮湿夜晚的天气参数设置，地面湿度较高，其他参数配合夜晚环境特点
  WP WP::WetNight = {     5.0f,    0.0f,    50.0f,    10.0f,    -1.0f,    -90.0f,    60.0f,     75.0f,     1.0f,   60.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 潮湿且多云夜晚的天气参数设置，结合潮湿和多云特点，适配夜晚时段的各参数设置
  WP WP::WetCloudyNight = {    60.0f,    0.0f,    50.0f,    10.0f,    -1.0f,    -90.0f,    60.0f,     0.75f,     0.1f,   60.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 小雨夜晚的天气参数设置，体现小雨强度，配合夜晚的其他环境参数
  WP WP::SoftRainNight = {    60.0f,   30.0f,    50.0f,    30.0f,    -1.0f,    -90.0f,    60.0f,     0.75f,     0.1f,   60.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 中雨夜晚的天气参数设置，降水相关参数体现中雨强度，配合夜晚时段其他参数
  WP WP::MidRainyNight = {    80.0f,   60.0f,    60.0f,    60.0f,    -1.0f,    -90.0f,    60.0f,     0.75f,     0.1f,   80.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 大雨夜晚的天气参数设置，降水强度大，各参数适配大雨夜晚的情况
  WP WP::HardRainNight = {   100.0f,  100.0f,    90.0f,    100.0f,   -1.0f,    -90.0f,   100.0f,     0.75f,     0.1f,  100.0f,   1.0f,   0.03f,   0.0331f,            0.0f };
  // 沙尘风暴天气参数设置，沙尘强度达到最大值，其他参数有相应的配合设置
  WP WP::DustStorm = {   100.0f,     0.0f,    0.0f,    100.0f,   -1.0f,     45.0f,     2.0f,     0.75f,     0.1f,    0.0f,   1.0f,   0.03f,   0.0331f,            100.0f  };

} // namespace rpc
} // namespace carla
