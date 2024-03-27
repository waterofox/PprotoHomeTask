import qbs
import "project_base.qbs" as ProjectBase
ProjectBase
{
    name: "TerminalClient";
    references:[
        "src/shared/shared.qbs",
        "src/yaml/yaml.qbs",
        "src/TerminalClient/TerminalClient.qbs",
        "src/pproto/pproto.qbs",
        "src/rapidjson/rapidjson.qbs",
        "src/commands/commands.qbs"
    ]
}
