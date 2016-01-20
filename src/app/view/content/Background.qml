import QtQuick 2.0
import QtQuick.Particles 2.0

ParticleSystem {
    id: root

    property alias color: r.color

    Rectangle {
        id: r
        z: -1
        anchors.fill: parent
    }

    /*
    Emitter {
        anchors.fill: parent
        emitRate: root.width * root.height / 500000
        lifeSpan: 30000
        size: dp(100)
        sizeVariation: dp(50)
        velocity: PointDirection {x: root.width/500; y: root.height/500; xVariation: -root.width/100; yVariation: -root.width/100}
        acceleration: PointDirection {x: 0; y: 0; xVariation: 0; yVariation: 0}
    }

    CustomParticle {
        vertexShader:"
            uniform lowp float qt_Opacity;
            varying lowp float fFade;
            varying highp vec2 fPos;

            void main() {
                qt_TexCoord0 = qt_ParticleTex;
                highp float size = qt_ParticleData.z;
                highp float endSize = qt_ParticleData.w;
                highp float t = (qt_Timestamp - qt_ParticleData.x) / qt_ParticleData.y;
                highp float currentSize = mix(size, endSize, t * t);

                if (t < 0. || t > 1.)
                currentSize = 0.;

                highp vec2 pos = qt_ParticlePos
                - currentSize / 2. + currentSize * qt_ParticleTex
                + qt_ParticleVec.xy * t * qt_ParticleData.y
                + 0.5 * qt_ParticleVec.zw * pow(t * qt_ParticleData.y, 2.);

                gl_Position = qt_Matrix * vec4(pos.x, pos.y, 0, 1);

                highp float fadeIn = min(t * 20., 1.);
                highp float fadeOut = 1. - max(0., min((t - 0.75) * 4., 1.));

                fFade = fadeIn * fadeOut * qt_Opacity;
                fPos = vec2(pos.x/320., pos.y/480.);
            }
        "
        fragmentShader: "
            varying highp vec2 fPos;
            varying lowp float fFade;
            varying highp vec2 qt_TexCoord0;
            void main() {
                highp vec2 circlePos = qt_TexCoord0*2.0 - vec2(1.0,1.0);
                highp float dist = length(circlePos);
                highp float circleFactor = max(min(1.0 - dist, 1.0), 0.0);
                gl_FragColor = vec4(fPos.x - fPos.y*2.0, 1. + fPos.y*2.0 - fPos.x, 1. + fPos.x*fPos.y*2.0, 0.0) * circleFactor * fFade;
            }
        "
    }
    */

    Rectangle {
        id: curtain
        anchors.fill: parent
        color: "black"
        opacity: 0.5
    }
}
