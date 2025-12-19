#include "Application.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

Application::Application() 
    : window(nullptr), selectedReaction(-1), showAbout(false), neatlyOutput(false), 
      leftPanelRatio(0.30f), middlePanelRatio(0.35f) {
}

Application::~Application() {
    cleanup();
}

bool Application::initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        return false;
    }

    // GL 3.3 + GLSL 330
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
                             "Chemical Reaction Simulator", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup style - Modern dark theme
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.WindowPadding = ImVec2(15, 15);
    style.FramePadding = ImVec2(8, 4);
    
    // Custom colors for a clean, modern look
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.35f, 0.45f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.30f, 0.45f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.40f, 0.55f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.30f, 0.50f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.28f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.34f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.20f, 0.25f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.40f, 0.70f, 1.00f, 1.00f);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load simulator data
    simulator.loadCompounds("resources/compounds");
    simulator.loadReactions("resources/reactions");
    
    // Initialize selection state
    selectedCompounds.resize(100, 0); // Max 100 compounds
    
    return true;
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render UI
        renderUI();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.12f, 0.12f, 0.14f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}

void Application::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Application::renderUI() {
    renderMenuBar();
    
    // Main window - fullscreen (below main menu bar)
    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT - 20));
    ImGui::Begin("Main", nullptr, 
                 ImGuiWindowFlags_NoTitleBar | 
                 ImGuiWindowFlags_NoResize | 
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse);

    // Informational note about layout
    ImGui::Text("Columns are auto-split; left column widened to 3/2 of previous");
    ImGui::Separator();

    // Three column layout - adjust left column to 3/2 of previous equal column
    float availableWidth = static_cast<float>(WINDOW_WIDTH) - 30.0f; // reserve padding
    float baseCol = availableWidth / 3.0f; // previous equal column width
    float leftWidth = baseCol * 1.5f; // 3/2 of previous
    if (leftWidth > availableWidth * 0.8f) leftWidth = availableWidth * 0.8f; // clamp
    float remaining = availableWidth - leftWidth;
    float middleWidth = remaining * 0.5f;
    float rightWidth = remaining - middleWidth;

    // Left panel - Compounds
    ImGui::BeginChild("CompoundsPanel", ImVec2(leftWidth, 0), true);
    renderCompoundList();
    ImGui::EndChild();

    ImGui::SameLine();

    // Middle panel - Reactions
    ImGui::BeginChild("ReactionsPanel", ImVec2(middleWidth, 0), true);
    renderReactionList();
    ImGui::EndChild();

    ImGui::SameLine();

    // Right panel - Simulation
    ImGui::BeginChild("SimulationPanel", ImVec2(rightWidth, 0), true);
    renderSimulationPanel();
    ImGui::EndChild();

    ImGui::End();

    // About dialog
    if (showAbout) {
        ImGui::Begin("About", &showAbout, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Chemical Reaction Simulator");
        ImGui::Separator();
        ImGui::Text("Version 1.0");
        ImGui::Text("Built with Dear ImGui, GLFW, OpenGL");
        ImGui::Text("\nA simple chemistry simulation tool");
        ImGui::End();
    }
}

void Application::renderMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Reload Resources")) {
                std::cout << "Reloading resources..." << std::endl;
                simulator.loadCompounds("resources/compounds");
                simulator.loadReactions("resources/reactions");
                selectedCompounds.clear();
                selectedCompounds.resize(static_cast<size_t>(simulator.getCompoundCount()), 0);
            }
            if (ImGui::MenuItem("Exit")) {
                glfwSetWindowShouldClose(window, true);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) {
                showAbout = true;
            }
            ImGui::EndMenu();
        }
        
        // Title in center
        ImGui::SetCursorPosX(WINDOW_WIDTH / 2 - 150);
        ImGui::TextColored(ImVec4(0.4f, 0.7f, 1.0f, 1.0f), "Chemical Reaction Simulator");
        
        ImGui::EndMainMenuBar();
    }
}

void Application::renderCompoundList() {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.7f, 1.0f, 1.0f));
    ImGui::Text("Compound Library");
    ImGui::PopStyleColor();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Select compounds to simulate:");
    ImGui::Spacing();

    // Display compounds with checkboxes
    for (size_t i = 0; i < simulator.getCompoundCount(); i++) {
        Compound* compound = simulator.getCompound(i);
        if (compound) {
            std::ostringstream labelStream;
            labelStream << compound->getName() << " (" << compound->getFormula() << ") - ";
            double mass = compound->getMolarMass();
            if (mass > 0.0) {
                labelStream << std::fixed << std::setprecision(2) << mass << " g/mol";
            } else {
                labelStream << "molar mass N/A";
            }
            std::string label = labelStream.str();

            // Add colored badge for state
            ImVec4 stateColor;
            if (compound->getState() == "gas") {
                stateColor = ImVec4(0.5f, 0.8f, 1.0f, 1.0f);
            } else if (compound->getState() == "liquid") {
                stateColor = ImVec4(0.4f, 0.7f, 1.0f, 1.0f);
            } else if (compound->getState() == "solid") {
                stateColor = ImVec4(0.8f, 0.6f, 0.4f, 1.0f);
            } else {
                stateColor = ImVec4(0.6f, 1.0f, 0.6f, 1.0f);
            }

            bool isSelected = (selectedCompounds[i] != 0);
            if (ImGui::Checkbox(("##compound" + std::to_string(i)).c_str(), &isSelected)) {
                selectedCompounds[i] = isSelected ? 1 : 0;
            }
            ImGui::SameLine();
            ImGui::TextColored(stateColor, "[%s]", compound->getState().c_str());
            ImGui::SameLine();
            ImGui::Text("%s", label.c_str());
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    
    if (ImGui::Button("Clear Selection", ImVec2(-1, 0))) {
        for (auto& selected : selectedCompounds) {
            selected = 0;
        }
        simulationResult.clear();
    }
}

void Application::renderReactionList() {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.7f, 1.0f, 1.0f));
    ImGui::Text("Reaction Library");
    ImGui::PopStyleColor();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Available reactions:");
    ImGui::Spacing();

    // Display reactions
    for (size_t i = 0; i < simulator.getReactionCount(); i++) {
        const Reaction* reaction = simulator.getReaction(i);
        if (reaction) {
            ImGui::PushID(i);
            
            bool isSelected = (selectedReaction == static_cast<int>(i));
            if (ImGui::Selectable(reaction->getName().c_str(), isSelected)) {
                selectedReaction = i;
            }
            
            ImGui::Indent(20);
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "%s", reaction->getEquation().c_str());
            ImGui::TextColored(ImVec4(0.6f, 0.8f, 0.6f, 1.0f), "Conditions: %s", reaction->getConditions().c_str());
            ImGui::Unindent(20);
            ImGui::Spacing();
            
            ImGui::PopID();
        }
    }
}

void Application::renderSimulationPanel() {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.7f, 1.0f, 1.0f));
    ImGui::Text("Simulation");
    ImGui::PopStyleColor();
    ImGui::Separator();
    ImGui::Spacing();

    // Show selected compounds
    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Selected Compounds:");
    ImGui::Spacing();
    
    std::vector<int> selectedIndices;
    for (size_t i = 0; i < selectedCompounds.size(); i++) {
        if (selectedCompounds[i]) {
            Compound* compound = simulator.getCompound(i);
            if (compound) {
                selectedIndices.push_back(i);
                ImGui::Text("  * %s (%s)", 
                    compound->getName().c_str(), 
                    compound->getFormula().c_str());
            }
        }
    }

    if (selectedIndices.empty()) {
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "  (none)");
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Simulate button
    if (ImGui::Button("Simulate Reaction", ImVec2(-1, 40))) {
        if (!selectedIndices.empty()) {
            std::ostringstream oss;
            
            // Get selected formulas
            std::vector<std::string> selectedFormulas;
            for (int idx : selectedIndices) {
                Compound* comp = simulator.getCompound(idx);
                if (comp) {
                    selectedFormulas.push_back(comp->getFormula());
                }
            }
            
            // Find matching reactions
            auto matches = simulator.findMatchingReactions(selectedFormulas);
            
            if (matches.empty()) {
                oss << "No reactions found for the selected compounds.\n\n";
                oss << "Try selecting different combinations.";
            } else {
                if (neatlyOutput) {
                    // Neatly output: only show equations
                    oss << "Possible Reactions:\n\n";
                    for (auto* reaction : matches) {
                        oss << reaction->getEquation() << "\n";
                    }
                } else {
                    // Detailed output: show full information
                    oss << "Possible Reactions:\n\n";
                    
                    for (auto* reaction : matches) {
                        oss << "===============================\n";
                        oss << "Reaction: " << reaction->getName() << "\n";
                        oss << "Equation: " << reaction->getEquation() << "\n";
                        oss << "Conditions: " << reaction->getConditions() << "\n\n";
                        
                        oss << "Products:\n";
                        for (const auto& product : reaction->getProducts()) {
                            // Find product in compound library
                            for (size_t i = 0; i < simulator.getCompoundCount(); i++) {
                                Compound* compound = simulator.getCompound(i);
                                if (compound && compound->getFormula() == product.first) {
                                    oss << "  * " << product.second << " x " 
                                        << compound->getName() << " (" << product.first << ")\n";
                                    break;
                                }
                            }
                        }
                        oss << "\n";
                    }
                }
            }
            
            simulationResult = oss.str();
        } else {
            simulationResult = "Please select at least one compound.";
        }
    }

    ImGui::Spacing();
    
    // Neatly Output checkbox - moved below button
    ImGui::Checkbox("Neatly Output", &neatlyOutput);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "(equations only)");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Results
    if (!simulationResult.empty()) {
        ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Results:");
        ImGui::Spacing();
        
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.15f, 0.17f, 1.0f));
        ImGui::BeginChild("Results", ImVec2(0, 0), true);
        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x);
        ImGui::TextWrapped("%s", simulationResult.c_str());
        ImGui::PopTextWrapPos();
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }
}
