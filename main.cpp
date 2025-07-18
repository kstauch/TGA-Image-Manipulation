#include <fstream>
#include <iostream>
#include <string>
#include "structs.h"

Image loadImage(const string &filepath);
void writeImage(Image &image, const string &filepath);
void clamp(int &value);
bool validFile(const string& filename);

void multiply(Image &tracking, const Image &other);
void subtract(Image &tracking_t, const Image &other_b);
void overlay(Image &tracking_t, const Image &other_b);
void screen(Image &tracking_b, const Image &other_t);
void combine(Image &tracking_red, Image &source_green, Image &source_blue);
void flip(Image &tracking);
void onlyred(Image &tracking);
void onlygreen(Image &tracking);
void onlyblue(Image &tracking);
void addred(Image &tracking, int amount);
void addgreen(Image &tracking, int amount);
void addblue(Image &tracking, int amount);
void scalered(Image &tracking, int amount);
void scalegreen(Image &tracking, int amount);
void scaleblue(Image &tracking, int amount);

/// command line input:
/// ./project2.out [output] [firstImage] [method] [...]
/// ./project2.out output/part20.tga input/car.tga multiply input/pattern.tga

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "Project 2: Image Processing, Summer 2025\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    } if (string(argv[1]) == "--help") {
        cout << "Project 2: Image Processing, Summer 2025\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    } if (argv[1] == nullptr) {
        cout << "Project 2: Image Processing, Summer 2025\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }


    const string outputPath = string(argv[1]);
    if (!validFile(outputPath)) {
        cout << "Invalid file name." << endl;
        return 1;
    }
    if (argv[2] == nullptr) {
        cout << "Invalid file name." << endl;
        return 1;
    }


    const string trackingPath = string(argv[2]);
    if (!validFile(trackingPath)) {
        cout << "Invalid file name." << endl;
        return 1;
    }
    Image tracking;
    try {
        tracking = loadImage(trackingPath);
    } catch (const runtime_error&) {
        cout << "File does not exist." << endl;
        return 1;
    }


    if (argv[3] == nullptr) {
        cout << "Invalid method name." << endl;
        return 1;
    }
    int index = 3;
    while (index < argc) {
        const string method = string(argv[index]);

        if (method == "multiply") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            } if (!validFile(argv[index+1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            Image argument;
            try {
                argument = loadImage(argv[index+1]);
            } catch (const runtime_error&) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            multiply(tracking, argument);
            index += 2;
        }

        else if (method == "subtract") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            } if (!validFile(argv[index+1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            Image argument;
            try {
                argument = loadImage(argv[index+1]);
            } catch (const runtime_error&) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            subtract(tracking, argument);
            index += 2;
        }

        else if (method == "overlay") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            } if (!validFile(argv[index+1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            Image argument;
            try {
                argument = loadImage(argv[index+1]);
            } catch (const runtime_error&) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            overlay(tracking, argument);
            index += 2;
        }

        else if (method == "screen") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            } if (!validFile(argv[index+1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            Image argument;
            try {
                argument = loadImage(argv[index+1]);
            } catch (const runtime_error&) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            screen(tracking, argument);
            index += 2;
        }

        else if (method == "combine") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            } if (!validFile(argv[index+1])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            Image firstArg;
            try {
                firstArg = loadImage(argv[index+1]);
            } catch (const runtime_error&) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            if (argv[index+2] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            } if (!validFile(argv[index+2])) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            Image secondArg;
            try {
                secondArg = loadImage(argv[index+2]);
            } catch (const runtime_error&) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            combine(tracking, firstArg, secondArg);
            index += 3;
        }

        else if (method == "flip") {
            flip(tracking);
            index += 1;
        }

        else if (method == "onlyred") {
            onlyred(tracking);
            index += 1;
        }

        else if (method == "onlygreen") {
            onlygreen(tracking);
            index += 1;
        }

        else if (method == "onlyblue") {
            onlyblue(tracking);
            index += 1;
        }

        else if (method == "addred") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            }
            int amount;
            try {
                amount = stoi(string(argv[index+1]));
            } catch (...) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            addred(tracking, amount);
            index += 2;
        }

        else if (method == "addgreen") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            }
            int amount;
            try {
                amount = stoi(string(argv[index+1]));
            } catch (...) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            addgreen(tracking, amount);
            index += 2;
        }

        else if (method == "addblue") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            }
            int amount;
            try {
                amount = stoi(string(argv[index+1]));
            } catch (...) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            addblue(tracking, amount);
            index += 2;
        }

        else if (method == "scalered") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            }
            int amount;
            try {
                amount = stoi(string(argv[index+1]));
            } catch (...) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            scalered(tracking, amount);
            index += 2;
        }

        else if (method == "scalegreen") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            }
            int amount;
            try {
                amount = stoi(string(argv[index+1]));
            } catch (...) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            scalegreen(tracking, amount);
            index += 2;
        }

        else if (method == "scaleblue") {
            if (argv[index+1] == nullptr) {
                cout << "Missing argument." << endl;
                return 1;
            }
            int amount;
            try {
                amount = stoi(string(argv[index+1]));
            } catch (...) {
                cout << "Invalid argument, expected number." << endl;
                return 1;
            }
            scaleblue(tracking, amount);
            index += 2;
        }

        else {
            cout << "Invalid method name." << endl;
            return 1;
        }

    }
    writeImage(tracking, outputPath);
    return 0;
}



Image loadImage(const string &filepath) {
    Header header{};
    Image image;

    ifstream file(filepath, ios::binary);

    if (!file.is_open())
        throw runtime_error("File did not open");
    // reading header
    file.read(&header.idLength, sizeof(header.idLength));
    file.read(&header.colorMapType, sizeof(header.colorMapType));
    file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.read(reinterpret_cast<char *>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    file.read(reinterpret_cast<char *>(&header.colorMapLength), sizeof(header.colorMapLength));
    file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.read(reinterpret_cast<char *>(&header.xOrigin), sizeof(header.xOrigin));
    file.read(reinterpret_cast<char *>(&header.yOrigin), sizeof(header.yOrigin));
    file.read(reinterpret_cast<char *>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char *>(&header.height), sizeof(header.height));
    file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    image.header = header;

    // skipping ID and/or color map if either is present
    file.seekg(header.idLength, ios::cur);
    if (header.colorMapType != 0)
        file.seekg(header.colorMapLength * (header.colorMapDepth / 8), ios::cur);

    // reading pixel data bottom left to top right
    for (int i = 0; i < header.height * header.width; i++) {
        Pixel pixel{};

        file.read(reinterpret_cast<char*>(&pixel.blue), sizeof(pixel.blue));
        file.read(reinterpret_cast<char*>(&pixel.green), sizeof(pixel.green));
        file.read(reinterpret_cast<char*>(&pixel.red), sizeof(pixel.red));

        image.pixels.push_back(pixel);
    }

    // cout << int(header.idLength) << "\n";
    // cout << int(header.colorMapType) << "\n";
    // cout << int(header.colorMapLength) << "\n";
    //
    // cout << image.pixels.size() << '\n';
    // cout << int(image.pixels[262143].blue) << '\n';
    // cout << int(image.pixels[262143].green) << '\n';
    // cout << int(image.pixels[262143].red) << "\n";


    file.close();
    return image;
}

void writeImage(Image &image, const string &filepath) {
    ofstream file(filepath, ios::binary);

    if (!file.is_open()) {
        cerr << "Output file did not open" << endl;
    }

    file.write(&image.header.idLength, sizeof(image.header.idLength));
    file.write(&image.header.colorMapType, sizeof(image.header.colorMapType));
    file.write(&image.header.dataTypeCode, sizeof(image.header.dataTypeCode));
    file.write(reinterpret_cast<char *>(&image.header.colorMapOrigin), sizeof(image.header.colorMapOrigin));
    file.write(reinterpret_cast<char *>(&image.header.colorMapLength), sizeof(image.header.colorMapLength));
    file.write(&image.header.colorMapDepth, sizeof(image.header.colorMapDepth));
    file.write(reinterpret_cast<char *>(&image.header.xOrigin), sizeof(image.header.xOrigin));
    file.write(reinterpret_cast<char *>(&image.header.yOrigin), sizeof(image.header.yOrigin));
    file.write(reinterpret_cast<char *>(&image.header.width), sizeof(image.header.width));
    file.write(reinterpret_cast<char *>(&image.header.height), sizeof(image.header.height));
    file.write(&image.header.bitsPerPixel, sizeof(image.header.bitsPerPixel));
    file.write(&image.header.imageDescriptor, sizeof(image.header.imageDescriptor));

    for (int i = 0; i < image.pixels.size(); i++) {
        file.write(reinterpret_cast<char *>(&image.pixels[i].blue), sizeof(image.pixels[i].blue));
        file.write(reinterpret_cast<char *>(&image.pixels[i].green), sizeof(image.pixels[i].green));
        file.write(reinterpret_cast<char *>(&image.pixels[i].red), sizeof(image.pixels[i].red));
    }
    file.close();
}

void clamp(int &value) {
    if (value < 0)
        value = 0;
    if (value > 255)
        value = 255;
}

bool validFile(const string& filename) {
    if (!(filename.size() >= 4 && filename.substr(filename.size() - 4) == ".tga"))
        return false;
    return true;
}



void multiply(Image &tracking, const Image &other) {
    for (int i = 0; i < tracking.pixels.size(); i++) {
        float normTopBlue = tracking.pixels[i].blue / 255.0f;
        float normBotBlue = other.pixels[i].blue / 255.0f;
        tracking.pixels[i].blue = static_cast<unsigned char>(normTopBlue * normBotBlue  * 255 + 0.5f);

        float normTopGreen = tracking.pixels[i].green / 255.0f;
        float normBotGreen = other.pixels[i].green / 255.0f;
        tracking.pixels[i].green = static_cast<unsigned char>(normTopGreen * normBotGreen  * 255 + 0.5f);

        float normTopRed = tracking.pixels[i].red / 255.0f;
        float normBotRed = other.pixels[i].red / 255.0f;
        tracking.pixels[i].red = static_cast<unsigned char>(normTopRed * normBotRed  * 255 + 0.5f);
    }
}
void subtract(Image &tracking_t, const Image &other_b) {
    for (int i = 0; i < tracking_t.pixels.size(); i++) {
        int newBlue = tracking_t.pixels[i].blue - other_b.pixels[i].blue;
        clamp(newBlue);
        tracking_t.pixels[i].blue = newBlue;

        int newGreen = tracking_t.pixels[i].green - other_b.pixels[i].green;
        clamp(newGreen);
        tracking_t.pixels[i].green = newGreen;

        int newRed = tracking_t.pixels[i].red - other_b.pixels[i].red;
        clamp(newRed);
        tracking_t.pixels[i].red = newRed;
    }
}
void overlay(Image &tracking_t, const Image &other_b) {
    for (int i = 0; i < tracking_t.pixels.size(); i++) {
        float channelResult;

        float normTopBlue = tracking_t.pixels[i].blue / 255.0f;
        float normBotBlue = other_b.pixels[i].blue / 255.0f;
        if (normBotBlue <= 0.5f) { // 2·NP1·NP2
            channelResult =  2 * normTopBlue * normBotBlue;
        } else { // 1 − [2·(1 − NP1)·(1 − NP2)]
            channelResult = 1 - (2 * (1 - normTopBlue) * (1 - normBotBlue));
        }
        tracking_t.pixels[i].blue = static_cast<unsigned char>(channelResult  * 255 + 0.5f);

        float normTopGreen = tracking_t.pixels[i].green / 255.0f;
        float normBotGreen = other_b.pixels[i].green / 255.0f;
        if (normBotGreen <= 0.5f) { // 2·NP1·NP2
            channelResult =  2 * normTopGreen * normBotGreen;
        } else { // 1 − [2·(1 − NP1)·(1 − NP2)]
            channelResult = 1 - (2 * (1 - normTopGreen) * (1 - normBotGreen));
        }
        tracking_t.pixels[i].green = static_cast<unsigned char>(channelResult  * 255 + 0.5f);

        float normTopRed = tracking_t.pixels[i].red / 255.0f;
        float normBotRed = other_b.pixels[i].red / 255.0f;
        if (normBotRed <= 0.5f) { // 2·NP1·NP2
            channelResult =  2 * normTopRed * normBotRed;
        } else { // 1 − [2·(1 − NP1)·(1 − NP2)]
            channelResult = 1 - (2 * (1 - normTopRed) * (1 - normBotRed));
        }
        tracking_t.pixels[i].red = static_cast<unsigned char>(channelResult  * 255 + 0.5f);

    }
}
void screen(Image &tracking_b, const Image &other_t) {
    for (int i = 0; i < tracking_b.pixels.size(); i++) {
        float normTopBlue = other_t.pixels[i].blue / 255.0f;
        float normBotBlue = tracking_b.pixels[i].blue / 255.0f;
        float screenResult = 1.0f - ((1.0f - normTopBlue) * (1.0f - normBotBlue));
        tracking_b.pixels[i].blue = static_cast<unsigned char>(screenResult  * 255.0f + 0.5f);

        float normTopGreen = other_t.pixels[i].green / 255.0f;
        float normBotGreen = tracking_b.pixels[i].green / 255.0f;
        screenResult = 1.0f - ((1.0f - normTopGreen) * (1.0f - normBotGreen));
        tracking_b.pixels[i].green = static_cast<unsigned char>(screenResult  * 255.0f + 0.5f);

        float normTopRed = other_t.pixels[i].red / 255.0f;
        float normBotRed = tracking_b.pixels[i].red / 255.0f;
        screenResult = 1.0f - ((1.0f - normTopRed) * (1.0f - normBotRed));
        tracking_b.pixels[i].red = static_cast<unsigned char>(screenResult  * 255.0f + 0.5f);
    }
}
void combine(Image &tracking_red, Image &source_green, Image &source_blue) {
    for (int i = 0; i < tracking_red.pixels.size(); i++) {
        tracking_red.pixels[i].blue = source_blue.pixels[i].blue;
        tracking_red.pixels[i].green = source_green.pixels[i].green;
    }
}
void flip(Image &tracking) {
    const vector<Pixel> copy = tracking.pixels;
    for (int i = 0; i < tracking.pixels.size(); i++) {
        tracking.pixels[i] = copy[tracking.pixels.size() - 1 - i];
    }
}
void onlyred(Image &tracking) {
    for (int i  = 0; i < tracking.pixels.size(); i++) {
        tracking.pixels[i].blue = tracking.pixels[i].red;
        tracking.pixels[i].green = tracking.pixels[i].red;
    }
}
void onlygreen(Image &tracking) {
    for (int i  = 0; i < tracking.pixels.size(); i++) {
        tracking.pixels[i].blue = tracking.pixels[i].green;
        tracking.pixels[i].red = tracking.pixels[i].green;
    }
}
void onlyblue(Image &tracking) {
    for (int i  = 0; i < tracking.pixels.size(); i++) {
        tracking.pixels[i].red = tracking.pixels[i].blue;
        tracking.pixels[i].green = tracking.pixels[i].blue;
    }
}

void addred(Image &tracking, int amount) {
    for (int i  = 0; i < tracking.pixels.size(); i++) {
        int newVal = tracking.pixels[i].red + amount;
        clamp(newVal);
        tracking.pixels[i].red = newVal;
    }
}

void addgreen(Image &tracking, int amount) {
    for (int i  = 0; i < tracking.pixels.size(); i++) {
        int newVal = tracking.pixels[i].green + amount;
        clamp(newVal);
        tracking.pixels[i].green = newVal;
    }
}

void addblue(Image &tracking, int amount) {
    for (int i  = 0; i < tracking.pixels.size(); i++) {
        int newVal = tracking.pixels[i].blue + amount;
        clamp(newVal);
        tracking.pixels[i].blue = newVal;
    }
}

void scalered(Image &tracking, int amount) {
    for (int i = 0; i < tracking.pixels.size(); i++) {
        float normRed = tracking.pixels[i].red / 255.0f;
        int newRed = static_cast<int>(normRed * amount * 255 + 0.5f);
        clamp(newRed);
        tracking.pixels[i].red = static_cast<unsigned char>(newRed);
    }
}

void scalegreen(Image &tracking, int amount) {
    for (int i = 0; i < tracking.pixels.size(); i++) {
        float normRed = tracking.pixels[i].green / 255.0f;
        int newRed = static_cast<int>(normRed * amount * 255 + 0.5f);
        clamp(newRed);
        tracking.pixels[i].green = static_cast<unsigned char>(newRed);
    }
}

void scaleblue(Image &tracking, int amount) {
    for (int i = 0; i < tracking.pixels.size(); i++) {
        float normRed = tracking.pixels[i].blue / 255.0f;
        int newRed = static_cast<int>(normRed * amount * 255 + 0.5f);
        clamp(newRed);
        tracking.pixels[i].blue = static_cast<unsigned char>(newRed);
    }
}


