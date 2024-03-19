import qbs
import "project_base.qbs" as ProjectBase
ProjectBase
{
    name: "Terminal";
    references:[
        "src/shared/shared.qbs",
        "src/yaml/yaml.qbs",
        "src/Terminal/Terminal.qbs",
        "src/pproto/pproto.qbs",
        "src/rapidjson/rapidjson.qbs",
        "src/commands/commands.qbs"
    ]
}
