#ifndef APPLICATION_H
#define APPLICATION_H

#include "ReactionSimulator.h"
#include <vector>
#include <string>

struct GLFWwindow;

/**
 * Main application class for the GUI
 */
class Application {
private:
    GLFWwindow* window;
    ReactionSimulator simulator;
    
    // UI State - Using char instead of bool to avoid std::vector<bool> issues
    std::vector<char> selectedCompounds;
    int selectedReaction;
    std::string simulationResult;
    bool showAbout;
    bool neatlyOutput;  // Option for clean output format
    
    // Window dimensions
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;

    // Resizable panel ratios (sum should be < 1.0, remainder used for spacing)
    float leftPanelRatio = 0.30f;
    float middlePanelRatio = 0.35f;
    
public:
    Application();
    ~Application();
    
    bool initialize();
    void run();
    void cleanup();
    
private:
    void renderUI();
    void renderCompoundList();
    void renderReactionList();
    void renderSimulationPanel();
    void renderMenuBar();
};

#endif // APPLICATION_H
