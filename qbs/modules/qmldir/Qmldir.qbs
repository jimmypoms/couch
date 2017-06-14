import qbs
import qbs.File

Module {
    FileTagger {
        patterns: ["qmldir"]
        fileTags: ["qmldir"]
    }

    Rule {
        inputs: ["qmldir"]

        Artifact {
            fileTags: ["dynamiclibrary"]
            filePath: product.destinationDirectory + "/qmldir"
        }

        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "copying qmldir: " + input.filePath + " -> " + output.filePath;
            cmd.highlight = "codegen";
            cmd.sourceCode = function() {
                File.copy(input.filePath, output.filePath)
            }
            return [cmd];
        }
    }
}