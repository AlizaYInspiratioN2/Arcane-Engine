# Arcane-Engine
Arcane Engine is a real-time game engine developed and maintained by [Tyrannical Games](https://ershany.github.io/). A large focus of this project is to develop an in-house engine catered to building indie games. Arcane's development roadmap will be game development driven, meaning it will be influenced by actually making games and prioritizing features needed to ship great indie games at [Tyrannical Games](https://ershany.github.io/)

![Arcane Logo](https://user-images.githubusercontent.com/11170417/79673959-8a210800-81ac-11ea-9474-3a44ee664152.png)

# Engine Showcases
[Tech Reel 2019](https://www.youtube.com/watch?v=sc02q6MXvVo)

## Engine Features
- Forward + Deferred Rendering (3D API)
- Debug Rendering API
- Physically Based Rendering (Fresnel on Everything)
- Cook Torrance Specular BRDF w/ Lambertian Diffuse
- PBR Material System
- Parallax Occlusion Mapping
- Light Probes (IBL)
- Reflection Probes (IBL)
- Linear Lighting (w/ Gamma Correction)
- HDR w/ Reinhard Tonemapper
- Screen Space Ambient Occlusion (SSAO)
- MSAA (Forward Path Anti-Aliasing)
- FXAA (Deferred Path Anti-Aliasing)
- Directional, Point, and Spot Light Sources
- Shadows for directional, point, and spot lights
- Skybox Support
- Terrain Material Blending
- Water + Wave Simulation
- Post Processing (Bloom, Film Grain, Chromatic Aberration, Vignette)
- Entity Component System
- Basic Animation Clip Player
- Emission Maps
- Displacement Maps

## Engine Libraries
- OpenGL 4.3+
- GLFW Input + Window
- Model Loading via ASSIMP (with bone data)
- ImGUI for UI
- STB for Image Loading
- EnTT for Component Storage and Management

## Development
If you want to see what I am currently working on check out Arcane's roadmap:
- [Rendering Trello](https://trello.com/b/WzD2bYCD/arcane-rendering)
- [Engine Trello](https://trello.com/b/Giv16bRX/arcane-engine)

## Roadmap for Arcane's Releases
[Arcane v0.1](https://github.com/Ershany/Arcane-Engine/milestone/1)

## Contributing
1. [Fork it](https://github.com/Ershany/Arcane-Engine.git)
1. Create your feature branch (`git checkout -b new-feature-branch`)
1. Commit your changes (`git commit -m "A description for your feature"`)
1. Push to the branch (`git push origin new-feature-branch`)
1. Create a new Pull Request

## Sources
- LearnOpenGL
- Game Engine Architecture
- Real-Time Rendering
- GPU Gems
- GPU Pro
- Hazel Series (YouTube)
ArkanAssistant_backup.jsx
import React, { useState, useEffect } from "react";

export default function ArkanAssistant() {
  const [message, setMessage] = useState("");
    const [chatLog, setChatLog] = useState([]);
      const [listening, setListening] = useState(false);
        const synth = window.speechSynthesis;
          let recognition;

            useEffect(() => {
                const history = JSON.parse(localStorage.getItem("arkan-history")) || [];
                    setChatLog(history);
                      }, []);

                        if ("webkitSpeechRecognition" in window) {
                            recognition = new window.webkitSpeechRecognition();
                                recognition.continuous = false;
                                    recognition.lang = "en-US";

                                        recognition.onresult = function (event) {
                                              const transcript = event.results[0][0].transcript;
                                                    setMessage(transcript);
                                                          sendMessage(transcript);
                                                              };

                                                                  recognition.onerror = recognition.onend = function () {
                                                                        setListening(false);
                                                                            };
                                                                              }

                                                                                const getResponse = async (msg) => {
                                                                                    try {
                                                                                          const res = await fetch("/arkan-chat", {
                                                                                                  method: "POST",
                                                                                                          headers: { "Content-Type": "application/json" },
                                                                                                                  body: JSON.stringify({ message: msg })
                                                                                                                        });
                                                                                                                              const data = await res.json();
                                                                                                                                    return data.reply;
                                                                                                                                        } catch (err) {
                                                                                                                                              return "Arkan had a problem connecting.";
                                                                                                                                                  }
                                                                                                                                                    };

                                                                                                                                                      const handleCommand = (msg) => {
                                                                                                                                                          const lower = msg.toLowerCase();
                                                                                                                                                              if (lower.includes("vin")) {
                                                                                                                                                                    document.getElementById("vin-iframe")?.scrollIntoView({ behavior: "smooth" });
                                                                                                                                                                        }
                                                                                                                                                                            if (lower.includes("bmw")) {
                                                                                                                                                                                  window.open("https://syrel.parts/bmw", "_blank");
                                                                                                                                                                                      }
                                                                                                                                                                                          if (lower.includes("inventory")) {
                                                                                                                                                                                                alert("Opening inventory module...");
                                                                                                                                                                                                    }
                                                                                                                                                                                                        if (lower.includes("clear chat")) {
                                                                                                                                                                                                              setChatLog([]);
                                                                                                                                                                                                                    localStorage.removeItem("arkan-history");
                                                                                                                                                                                                                          speak("Chat cleared.");
                                                                                                                                                                                                                              }
                                                                                                                                                                                                                                  if (lower.includes("restart")) {
                                                                                                                                                                                                                                        speak("Restarting...");
                                                                                                                                                                                                                                              setTimeout(() => window.location.reload(), 800);
                                                                                                                                                                                                                                                  }
                                                                                                                                                                                                                                                    };

                                                                                                                                                                                                                                                      const speak = (text, lang = "en-US") => {
                                                                                                                                                                                                                                                          const utterance = new SpeechSynthesisUtterance(text);
                                                                                                                                                                                                                                                              utterance.lang = lang;
                                                                                                                                                                                                                                                                  synth.speak(utterance);
                                                                                                                                                                                                                                                                    };

                                                                                                                                                                                                                                                                      const sendMessage = async (text) => {
                                                                                                                                                                                                                                                                          handleCommand(text);
                                                                                                                                                                                                                                                                              const reply = await getResponse(text);
                                                                                                                                                                                                                                                                                  const newLog = [...chatLog, { from: "you", text }, { from: "arkan", text: reply }];
                                                                                                                                                                                                                                                                                      setChatLog(newLog);
                                                                                                                                                                                                                                                                                          localStorage.setItem("arkan-history", JSON.stringify(newLog));
                                                                                                                                                                                                                                                                                              setMessage("");
                                                                                                                                                                                                                                                                                                  speak(reply);
                                                                                                                                                                                                                                                                                                      fetch("/log", {
                                                                                                                                                                                                                                                                                                            method: "POST",
                                                                                                                                                                                                                                                                                                                  headers: { "Content-Type": "application/json" },
                                                                                                                                                                                                                                                                                                                        body: JSON.stringify({ text: reply, source: "arkan" })
                                                                                                                                                                                                                                                                                                                            });
                                                                                                                                                                                                                                                                                                                              };

                                                                                                                                                                                                                                                                                                                                return (
                                                                                                                                                                                                                                                                                                                                    <div style={{ padding: "15px", borderTop: "1px solid #ccc", marginTop: "20px" }}>
                                                                                                                                                                                                                                                                                                                                          <h3>🔧 Arkan Assistant (Backup Version)</h3>
                                                                                                                                                                                                                                                                                                                                                <div style={{ height: "150px", overflowY: "auto", border: "1px solid #eee", padding: "5px" }}>
                                                                                                                                                                                                                                                                                                                                                        {chatLog.map((entry, i) => (
                                                                                                                                                                                                                                                                                                                                                                  <div key={i} style={{ textAlign: entry.from === "you" ? "right" : "left" }}>
                                                                                                                                                                                                                                                                                                                                                                              <strong>{entry.from}:</strong> {entry.text}
                                                                                                                                                                                                                                                                                                                                                                                        </div>
                                                                                                                                                                                                                                                                                                                                                                                                ))}
                                                                                                                                                                                                                                                                                                                                                                                                      </div>
                                                                                                                                                                                                                                                                                                                                                                                                            <input
                                                                                                                                                                                                                                                                                                                                                                                                                    value={message}
                                                                                                                                                                                                                                                                                                                                                                                                                            onChange={(e) => setMessage(e.target.value)}
                                                                                                                                                                                                                                                                                                                                                                                                                                    placeholder="Type your message"
                                                                                                                                                                                                                                                                                                                                                                                                                                            style={{ width: "60%", marginTop: "10px" }}
                                                                                                                                                                                                                                                                                                                                                                                                                                                  />
                                                                                                                                                                                                                                                                                                                                                                                                                                                        <button onClick={() => sendMessage(message)} style={{ marginLeft: "10px" }}>Send</button>
                                                                                                                                                                                                                                                                                                                                                                                                                                                              <button
                                                                                                                                                                                                                                                                                                                                                                                                                                                                      onClick={() => {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                if (listening) {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            recognition.stop();
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      } else {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  recognition.start();
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              setListening(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        style={{ marginLeft: "10px" }}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              >
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      {listening ? "🛑 Stop Mic" : "🎤 Speak"}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            </button>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                </div>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  );
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  