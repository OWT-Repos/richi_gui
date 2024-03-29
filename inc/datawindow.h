#pragma once

#include <QString>
#include <cmath>
#include <vector>

// Class to generate a data processing window
class DataWindow {
   public:
    // Window types
    enum {
        NOWINDOW = 0,
        HAMMING,
        HANNING,
        BLACKMAN,
        NUTALL,
        BLACKMAN_NUTTALL,
        BLACKMAN_HARRIS
    };

    static QString windowName(const int windowOption) {
        switch (windowOption) {
            case 0:
                return QCoreApplication::translate("MainWindow", "No Window");
            case 1:
                return QCoreApplication::translate("MainWindow", "Window Hamming");
            case 2:
                return QCoreApplication::translate("MainWindow", "Window Hanning");
            case 3:
                return QCoreApplication::translate("MainWindow", "Window Blackman");
            case 4:
                return QCoreApplication::translate("MainWindow", "Window Nutall");
            case 5:
                return QCoreApplication::translate("MainWindow", "Window Bl-Nutall");
            case 6:
                return QCoreApplication::translate("MainWindow", "Window Bl-Harris");
            default:
                return QCoreApplication::translate("MainWindow", "No Window");
        }
    }

    // Returns a window with size and type given by the arguments
    static std::vector<double> createWindow(const int size, const int windowName) {
        std::vector<double> coefficients = std::vector<double>(size);
        switch (windowName) {
            case NOWINDOW:
                for (int i = 0; i < size; i++) {
                    coefficients[i] = 1.0;
                }
                break;
            case HAMMING:
                for (int i = 0; i < size; i++) {
                    coefficients[i] = 0.5 - 0.5 * cos(2 * M_PI * i / size);
                }
                break;
            case HANNING:
                for (int i = 0; i < size; i++) {
                    coefficients[i] = 0.5 - 0.543478 * cos(2 * M_PI * i / size);
                }
                break;
            case BLACKMAN:
                for (int i = 0; i < size; i++) {
                    coefficients[i] = 0.42659 - 0.49656 * cos(2 * M_PI * i / size) + 0.076849 * cos(4 * M_PI * i / size);
                }
                break;
            case NUTALL:
                for (int i = 0; i < size; i++) {
                    coefficients[i] = 0.355768 - 0.487396 * cos(2 * M_PI * i / size) + 0.144232 * cos(4 * M_PI * i / size) - 0.012604 * cos(6 * M_PI * i / size);
                }
                break;
            case BLACKMAN_NUTTALL:
                for (int i = 0; i < size; i++) {
                    coefficients[i] = 0.3635819 - 0.4891775 * cos(2 * M_PI * i / size) + 0.1365995 * cos(4 * M_PI * i / size) - 0.0106411 * cos(6 * M_PI * i / size);
                }
                break;
            case BLACKMAN_HARRIS:
                for (int i = 0; i < size; i++) {
                    coefficients[i] = 0.35875 - 0.48829 * cos(2 * M_PI * i / size) + 0.14128 * cos(4 * M_PI * i / size) - 0.01168 * cos(6 * M_PI * i / size);
                }
                break;
        }
        return coefficients;
    };
};