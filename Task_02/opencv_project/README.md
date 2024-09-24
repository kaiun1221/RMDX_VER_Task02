# RoboMaster 笃行-视觉组培训第二次作业笔记


## 1. 组织项目结构
由於希望可以從一開始便寫READE.md，所以第一步先將結構寫好
在組织时按照任务书教学建立,并没遇到报错
在vscode写README.md文档时遇到了无法输入中文（由於我使用倉頡输入法，相比拼音而言能找到的解決方法會更少）的问题:
1.首先我找到了[CSDN教程1](https://blog.csdn.net/szm1234/article/details/110819676)尝試重裝，無改變
2.再找到[CSDN教程2](https://blog.csdn.net/DpgrMl/article/details/133265063)在免費內容中的方法尝試設定，沒找到該設定項
3.思考时想到有机会是输入法问题,根据[知乎教程](https://zhuanlan.zhihu.com/p/563224248)将系统自带输入法换成Fctix5输入法,成功解决问题

## 2. 配置环境  
C++环境在之前已经安装过，无需再次安装  
OpenCV库的配置跟随[CSDN教程](https://blog.csdn.net/weixin_44796670/article/details/115900538)执行，并无报错

## 3.实现基础图像处理操作
在这一步我尝试询问了gpt4o,对话如下:
    我:如何使用opencv VSCODE C++对图片进行图像颜色空间转换:转化为灰度图,转化为 HSV 图片
    gpt4o:  
    使用 OpenCV 在 VS Code 中编写 C++ 代码来进行图像颜色空间转换，包括将图像转换为灰度图和 HSV 图，可以按照以下步骤进行：

        ### 1. 安装 OpenCV

        首先，你需要在系统上安装 OpenCV。你可以通过以下命令安装 OpenCV：

        ```bash
        sudo apt update
        sudo apt install libopencv-dev
        ```

        ### 2. 配置 VS Code

        确保你已经安装了 C++ 扩展插件（C/C++ by Microsoft）以支持 C++ 编程。

        ### 3. 创建项目目录

        创建一个新的项目目录并进入该目录：

        ```bash
        mkdir opencv_project
        cd opencv_project
        ```

        ### 4. 创建 C++ 源文件

        创建一个名为 `main.cpp` 的文件，并添加以下代码：

        ```cpp
        #include <opencv2/opencv.hpp>
        #include <iostream>

        using namespace cv;
        using namespace std;

        int main(int argc, char** argv) {
            // 检查是否提供了图像路径
            if (argc != 2) {
                cout << "Usage: " << argv[0] << " <Image_Path>" << endl;
                return -1;
            }

            // 读取图像
            Mat image = imread(argv[1], IMREAD_COLOR);
            if (image.empty()) {
                cout << "Could not open or find the image" << endl;
                return -1;
            }

            // 转换为灰度图
            Mat grayImage;
            cvtColor(image, grayImage, COLOR_BGR2GRAY);

            // 转换为 HSV 图像
            Mat hsvImage;
            cvtColor(image, hsvImage, COLOR_BGR2HSV);

            // 显示原图像
            namedWindow("Original Image", WINDOW_AUTOSIZE);
            imshow("Original Image", image);

            // 显示灰度图
            namedWindow("Gray Image", WINDOW_AUTOSIZE);
            imshow("Gray Image", grayImage);

            // 显示 HSV 图像
            namedWindow("HSV Image", WINDOW_AUTOSIZE);
            imshow("HSV Image", hsvImage);

            // 等待用户按键
            waitKey(0);

            return 0;
        }
        ```

        ### 5. 创建 CMake 文件

        创建一个名为 `CMakeLists.txt` 的文件，并添加以下内容：

        ```cmake
        cmake_minimum_required(VERSION 3.10)
        project(OpenCVProject)

        # 设置 C++ 标准
        set(CMAKE_CXX_STANDARD 11)

        # 查找 OpenCV 包
        find_package(OpenCV REQUIRED)

        # 添加可执行文件
        add_executable(OpenCVProject main.cpp)

        # 链接 OpenCV 库
        target_link_libraries(OpenCVProject ${OpenCV_LIBS})
        ```

        ### 6. 编译和运行项目

        在项目目录中创建一个 `build` 目录并进入该目录：

        ```bash
        mkdir build
        cd build
        ```

        使用 CMake 配置并构建项目：

        ```bash
        cmake ..
        make
        ```

        编译完成后，你可以运行生成的可执行文件，并传递图像路径作为参数：

        ```bash
        ./OpenCVProject ../path/to/your/image.jpg
        ```

        ### 7. 运行结果

        程序将会显示三个窗口，分别显示原图像、灰度图和 HSV 图像。

    通过这些步骤，你可以在 VS Code 中使用 OpenCV 和 C++ 进行图像颜色空间转换。如果你在执行这些步骤时遇到任何问题，请提供具体的错误信息或行为描述，以便进一步诊断和解决问题。


我希望逐步尝试,只取了显示图像部份,代码如下:

    #include <opencv2/opencv.hpp>
    #include <opencv2/highgui.hpp>
    #include <opencv2/imgproc.hpp>
    #include <iostream>

    int main()
    {
        cv::Mat image = cv::imread("../resource/test_image.png");
        cv::imshow("Image", image);

    }

但开始遇到以下问题:

    在#include <opencv2/opencv.hpp>中发现报错:检测到 #include 错误。请更新 includePath。已为此翻译单元(/home/kaiun1221/RMDX/Task_02/opencv_project/src/main.cpp)禁用波形曲线。C/C++(1696)

我继续询问gpt4o,其回覆内容如下:
    
    要在基于 Debian 的系统（如 Ubuntu）上使用 `apt` 安装 `g++` 和 `curl`，你可以执行以下命令：

    ### 1. 更新软件包列表

    首先，确保你的软件包列表是最新的：

    ```bash
    sudo apt update
    ```

    ### 2. 安装 `g++`

    `g++` 是 GNU 编译器集合中的 C++ 编译器。你可以使用以下命令安装它：

    ```bash
    sudo apt install g++
    ```

    ### 3. 安装 `curl`

    `curl` 是一个用于传输数据的命令行工具，支持多种协议。你可以使用以下命令安装它：

    ```bash
    sudo apt install curl
    ```

    ### 4. 验证安装

    安装完成后，你可以通过以下命令验证 `g++` 和 `curl` 是否已正确安装：

    ```bash
    g++ --version
    curl --version
    ```

    这两个命令应该会输出相应的软件版本信息，确认它们已成功安装。

    ### 总结

    以下是完整的命令列表，供参考：

    ```bash
    sudo apt update
    sudo apt install g++
    sudo apt install curl
    ```

    执行这些命令后，你的系统应该会安装 `g++` 和 `curl`，并且你可以开始使用它们了。如果在安装过程中遇到任何问题，请提供具体的错误信息，以便进一步诊断和解决。

根据gpt4o教程修改,并没有用
之後再在CSDN上找到教程(连结已遗失),根据教程修改"c_cpp_properties.json"代码为:

    {
        "configurations": [
            {
                "name": "Linux",
                "includePath": [
                    "/usr/include",
                    "${workspaceFolder}/**",
                    "/usr/include/c++/11",
                    "/usr/include/x86_64-linux-gnu/c++/11",
                    "/usr/include/c++/11/backward",
                    "/usr/lib/gcc/x86_64-linux-gnu/11/include",
                    "/usr/local/include",
                    "/usr/include/x86_64-linux-gnu"
                ],
                "defines": [],
                "cStandard": "c17",
                "cppStandard": "gnu++17",
                "intelliSenseMode": "linux-gcc-x64",
                "compilerPath": ""
            }
        ],
        "version": 4
    }

报错成功解决

继续执行代码,遇到报错如下:

    [Running] cd "/home/kaiun1221/RMDX/Task_02/opencv_project/src/" && g++ main.cpp -o main && "/home/kaiun1221/RMDX/Task_02/opencv_project/src/"main
    main.cpp:1:10: fatal error: opencv2/opencv.hpp: No such file or directory
        1 | #include <opencv2/opencv.hpp>
        |          ^~~~~~~~~~~~~~~~~~~~
    compilation terminated.

    [Done] exited with code=1 in 0.023 seconds

将报错发送到gpt4o,其回覆如下:

    这个错误表明编译器无法找到 OpenCV 的头文件。这个问题通常与 CMake 没有正确找到 OpenCV 安装位置有关。以下是一些可能的解决方案：
    确保 OpenCV 已安装

    首先，确保你的系统上已经安装了 OpenCV。如果没有安装，你可以使用包管理器来安装。例如，在 Ubuntu 上可以使用以下命令：

    sudo apt-get update
    sudo apt-get install libopencv-dev

    检查 OpenCV 安装路径

    确保 OpenCV 安装在系统的标准路径中，或者你知道它的安装路径。你可以使用以下命令来查找 OpenCV 的头文件位置：

    pkg-config --cflags opencv4

    修改 CMakeLists.txt

    如果 OpenCV 安装在非标准路径中，你可能需要在 CMakeLists.txt 中手动指定 OpenCV 的路径。以下是一个修改后的 CMakeLists.txt 示例：

    cmake_minimum_required(VERSION 3.10)
    project(MyOpenCVProject)

    # 设置 C++ 标准
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)

    # 查找 OpenCV 包
    find_package(OpenCV REQUIRED PATHS /path/to/your/opencv)

    # 包含 OpenCV 头文件
    include_directories(${OpenCV_INCLUDE_DIRS})

    # 添加可执行文件
    add_executable(MyOpenCVProject src/main.cpp)

    # 链接 OpenCV 库
    target_link_libraries(MyOpenCVProject ${OpenCV_LIBS})

    将 /path/to/your/opencv 替换为 OpenCV 安装的实际路径。
    清理并重新生成构建文件

    有时候，CMake 缓存会导致问题。你可以尝试删除 build 目录并重新生成构建文件：

    rm -rf build
    mkdir build
    cd build
    cmake ..
    make
    ./MyOpenCVProject

    检查 CMake 输出

    在运行 cmake .. 时，注意输出信息，确保 CMake 能正确找到 OpenCV。如果 CMake 找不到 OpenCV，会在输出中显示错误信息。
    示例输出

    如果一切正常，运行 cmake .. 时，你应该看到类似以下的输出：

    -- Found OpenCV: /usr/local (found version "4.x.x")
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /path/to/your/project/build

    总结

        确保 OpenCV 已正确安装。
        使用 pkg-config 检查 OpenCV 的头文件路径。
        在 CMakeLists.txt 中手动指定 OpenCV 的安装路径（如果必要）。
        清理并重新生成构建文件。
        检查 CMake 输出，确保它能正确找到 OpenCV。

    通过这些步骤，你应该能够解决编译器找不到 OpenCV 头文件的问题。


根据gpt4o教程操作,问题并未解决,继续多次询问gpt4o解决方法及细节(inculde内容错误,路径应为绝对路径等我认为有可能的问题),但都得到否定回答,问题仍未解决

于[CSDN](https://blog.csdn.net/nyist_yangguang/article/details/120442945)尝试重装,没效果

最後选择问群友,群友方法无效

20240924 直接问学长,发现是因为CMakeLists.txt中的find_package(OpenCV REQUIRED) 顺序问题,问题解决

原代码来源为直接使用任务书中要求询问gpt4o获得,直接执行发现HSV调红色的图片是全黑的,後续再问gpt4o得出新的代码如下:

    // 定义红色的低色调和高色调范围
    cv::Mat lowerRedMask, upperRedMask;
    cv::inRange(hsvImage, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowerRedMask);
    cv::inRange(hsvImage, cv::Scalar(170, 100, 100), cv::Scalar(180, 255, 255), upperRedMask);

    // 合并低色调和高色调的红色掩码
    cv::Mat redMask;
    cv::addWeighted(lowerRedMask, 1.0, upperRedMask, 1.0, 0.0, redMask);

    // 保存红色掩码图像
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/red_mask.png", redMask);

修改後没有问题出现.

之後对gpt4o写出的代码输出的图像进行核对,过程中使用gpt4o询问各图像应有的特征,并没有发现错误

## 4.项目构建与运行
按照任务书教程进行,并无报错

## 5.提交任务源代码以及 README
按照任务书教程进行,并无报错
