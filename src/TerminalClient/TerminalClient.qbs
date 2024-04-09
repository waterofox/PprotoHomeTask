import qbs
import QbsUtl

Product
{
    type: "application"
    consoleApplication: true

    Depends{name: "cpp"}
    Depends { name: "Commands"}
    Depends{name: "PProto"}
    Depends{name: "RapidJson"}
    Depends{name: "SharedLib"}
    Depends{name: "Yaml"}
    Depends{ name: "Qt"; submodules: ["core","network","sql","gui","widgets"]}

    cpp.defines: project.cppDefines
    cpp.cxxLanguageVersion: project.cxxLanguageVersion

    cpp.systemIncludePaths: Qt.core.cpp.includePaths

    files:[
        "client.cpp",
        "client.h",
        "main.cpp",
        "widgets/messenger_main_form.cpp",
        "widgets/messenger_main_form.h",
        "widgets/messenger_main_form.ui",
    ]
}
