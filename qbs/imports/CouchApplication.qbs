import qbs 1.0

CppApplication {
    property path includePath: project.sourceDirectory + "/include"

    destinationDirectory: project.buildDirectory + "/bin"

    cpp.includePaths: [includePath]
    cpp.cxxLanguageVersion: "c++11"
    cpp.enableRtti: false
    cpp.rpaths: [project.buildDirectory + "/lib/couch"]

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