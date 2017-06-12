import qbs 1.0

DynamicLibrary {
    property path includePath: project.sourceDirectory + "/include"
    destinationDirectory: project.buildDirectory + "/lib/couch"

    Depends { name: "cpp" }

    cpp.includePaths: [includePath]
    cpp.libraryPaths: [destinationDirectory]
    cpp.cxxLanguageVersion: "c++11"
    cpp.enableRtti: false

    Properties {
        condition: qbs.buildVariant == "debug"
        cpp.debugInformation: true
        cpp.optimization: "none"
        cpp.warningLevel: "all"
    }
    Properties {
        condition: qbs.buildVariant == "release"
        cpp.debugInformation: false
        cpp.optimization: "fast"
        cpp.warningLevel: "none"
    }
}