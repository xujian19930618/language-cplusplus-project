
# 1. 指定基础镜像：选用官方最新稳定版 Fedora
FROM fedora:44

# 2. 维护者信息（可选，用于标识镜像制作者）

# 3. 升级系统包并安装 C/C++ 开发必需依赖
# dnf -y：自动确认安装，--refresh：刷新软件源缓存
# 核心依赖说明：
#   gcc：C 语言编译器
#   gcc-c++：C++ 语言编译器（g++）
#   make：传统构建工具
#   cmake：跨平台构建工具（现代 C/C++ 项目常用）
#   glibc-devel：GNU C 标准库开发文件（提供头文件、链接库等）
#   libstdc++-devel：C++ 标准库开发文件
#   git：版本控制工具（可选，开发中常用）
RUN dnf clean all && dnf -y --refresh upgrade && dnf -y install gcc gcc-c++ make cmake glibc-devel libstdc++-devel git && dnf clean all && rm -rf /var/cache/dnf/*


CMD ["tail", "-f", "/dev/null"]