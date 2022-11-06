#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include <unistd.h>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
sf::RenderWindow window(sf::VideoMode(960, 600), "Sorter");
sf::Event event;
int n = 66;
float recH[66];
unsigned int microsecond = 10000; // 1 second
bool sorted = false;

SoundBuffer sound ;
Sound so ;

sf::Font font;
//bubbleSortBtn
sf::RectangleShape bubbleSortBtn(sf::Vector2f(100, 50));
sf::Text bubbleSortText;

//selectionSortBtn
sf::RectangleShape selectionSortBtn(sf::Vector2f(100, 50));
sf::Text selectionSortText;

//insertionSortBtn
sf::RectangleShape insertionSortBtn(sf::Vector2f(100, 50));
sf::Text insertionSortText;

//mergeSortBtn
sf::RectangleShape mergeSortBtn(sf::Vector2f(100, 50));
sf::Text mergeSortText;

//quickSortBtn
sf::RectangleShape quickSortBtn(sf::Vector2f(100, 50));
sf::Text quickSortText;

//heapSortBtn
sf::RectangleShape heapSortBtn(sf::Vector2f(100, 50));
sf::Text heapSortText;

void drawSorted() {
    window.clear();

    window.draw(bubbleSortBtn);
    window.draw(insertionSortBtn);
    window.draw(selectionSortBtn);
    window.draw(mergeSortBtn);
    window.draw(quickSortBtn);
    window.draw(heapSortBtn);

    window.draw(bubbleSortText);
    window.draw(insertionSortText);
    window.draw(selectionSortText);
    window.draw(mergeSortText);
    window.draw(quickSortText);
    window.draw(heapSortText);

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++)
        {
            sf::RectangleShape block(sf::Vector2f(10, recH[i]));
            block.setPosition(200 + i * 12, 600 - recH[i]);
            block.setFillColor(sf::Color::White);
            if (i <= j)
                block.setFillColor(sf::Color::Green);
            window.draw(block);
        }
        window.display();
    }
}

void draw(int idx1, int idx2, int left, int mid, int right) {
    window.clear();

    window.draw(bubbleSortBtn);
    window.draw(insertionSortBtn);
    window.draw(selectionSortBtn);
    window.draw(mergeSortBtn);
    window.draw(quickSortBtn);
    window.draw(heapSortBtn);

    window.draw(bubbleSortText);
    window.draw(insertionSortText);
    window.draw(selectionSortText);
    window.draw(mergeSortText);
    window.draw(quickSortText);
    window.draw(heapSortText);

    cout << left << " " << mid << " " << right << endl;
    cout << idx1 << " " << idx2 << endl;
    for (int i = 0; i < n; i++)
    {
        sf::RectangleShape block(sf::Vector2f(11, recH[i]));
        block.setPosition(200 + i * 12, 600 - recH[i]);
        block.setFillColor(sf::Color::White);

        if (i == idx1 || i == idx2) {
            block.setFillColor(sf::Color::Green);
        }
        else if (i == left || i == right) {
            block.setFillColor(sf::Color::Red);
        }
        else if (i == mid) {
            block.setFillColor(sf::Color::Blue);
        }
        else {
            block.setFillColor(sf::Color::White);
        }
        window.draw(block);
    }
    window.display();
}

//bubbleSort
void bubbleSort()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (recH[j] > recH[j + 1])
            {
                swap(recH[j], recH[j + 1]);
                draw(j, j + 1, -1, -1, -1);
            }
        }

    }
}
//selectionSort
void selectionSort()
{
    int min_idx;
    for (int i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (recH[j] < recH[min_idx])
            {
                so.play();
                min_idx = j;
            }

        draw(min_idx, j, -1, -1, -1);
        }
        swap(recH[min_idx], recH[i]);
    }
}
//insertionSort
void insertionSort()
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = recH[i];
        j = i - 1;
        while (j >= 0 && recH[j] > key)
        {
            recH[j + 1] = recH[j];
            j = j - 1;
            draw(j , i, -1, -1, -1);
        }
        recH[j + 1] = key;
    }
}
//mergeSort
void merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
    {
        L[i] = recH[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = recH[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            recH[k] = L[i];
            i++;
        draw(l + i, -1, l, k, r);
        }
        else
        {
            recH[k] = R[j];
            j++;
            draw(-1, m + j, l, k, r);
        }
        k++;
    }
    while (i < n1)
    {
        recH[k] = L[i];
        i++;
        k++;
        draw(l + i, -1, l, k, r);
    }
    while (j < n2)
    {
        recH[k] = R[j];
        j++;
        k++;
        draw(-1, m + j, l, k, r);
    }
}
void mergeSort(int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}
//quickSort
int partition(int low, int high)
{
    int pivot = recH[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (recH[j] < pivot)
        {
            i++;
            swap(recH[i], recH[j]);
        }
        draw(i, j, low, -1, high);
    }
    swap(recH[i + 1], recH[high]);
    draw(i + 1, high, low, -1, high);
    return (i + 1);
}
void quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}
//heapSort
void heapify(int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && recH[l] > recH[largest])
    {
        largest = l;
    }
    if (r < n && recH[r] > recH[largest])
    {
        largest = r;
    }
    if (largest != i)
    {
        swap(recH[i], recH[largest]);
        heapify(n, largest);
    }
    draw(i, largest, -1, -1, -1);
}
void heapSort()
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(recH[0], recH[i]);
        draw(0, i, -1, -1, -1);
        heapify(i, 0);
    }
}

void sortAgain(){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x >= 0 && mousePos.x <= 100 && mousePos.y >= 0 && mousePos.y <= 50)
        {
            sorted = false;
            for (int i = 0; i < n; i++)
            {
                recH[i] = rand() % 500 + 1;
            }
        }
    }
}
void reset()
{
    for (int i = 0; i < n; i++)
    {
        recH[i] = rand() % 600;
    }
    sorted = false;
}
//change the sort type
int main()
{
    sound.loadFromFile("sort5.wav") ;
    so.setBuffer(sound);

    window.create(sf::VideoMode(1000, 600), "Sorting Visualizer");
    window.setFramerateLimit(60);

    for (int i = 0; i < n; i++)
    {
        recH[i] = rand() % 600;
    }

    font.loadFromFile("arial.ttf");

    bubbleSortText.setFont(font);
    bubbleSortText.setString("Bubble Sort");
    bubbleSortText.setCharacterSize(20);
    bubbleSortText.setFillColor(sf::Color::Black);

    selectionSortText.setFont(font);
    selectionSortText.setString("Selection Sort");
    selectionSortText.setCharacterSize(20);
    selectionSortText.setFillColor(sf::Color::Black);

    insertionSortText.setFont(font);
    insertionSortText.setString("Insertion Sort");
    insertionSortText.setCharacterSize(20);
    insertionSortText.setFillColor(sf::Color::Black);

    mergeSortText.setFont(font);
    mergeSortText.setString("Merge Sort");
    mergeSortText.setCharacterSize(20);
    mergeSortText.setFillColor(sf::Color::Black);

    quickSortText.setFont(font);
    quickSortText.setString("Quick Sort");
    quickSortText.setCharacterSize(20);
    quickSortText.setFillColor(sf::Color::Black);

    heapSortText.setFont(font);
    heapSortText.setString("Heap Sort");
    heapSortText.setCharacterSize(20);
    heapSortText.setFillColor(sf::Color::Black);

    bubbleSortBtn.setPosition(10, 100);
    insertionSortBtn.setPosition(10, 150);
    selectionSortBtn.setPosition(10, 200);
    mergeSortBtn.setPosition(10, 250);
    quickSortBtn.setPosition(10, 300);
    heapSortBtn.setPosition(10, 350);

    bubbleSortText.setPosition(20, 110);
    insertionSortText.setPosition(20, 160);
    selectionSortText.setPosition(20, 210);
    mergeSortText.setPosition(20, 260);
    quickSortText.setPosition(20, 310);
    heapSortText.setPosition(20, 360);

    bubbleSortBtn.setSize(sf::Vector2f(170, 50));
    insertionSortBtn.setSize(sf::Vector2f(170, 50));
    selectionSortBtn.setSize(sf::Vector2f(170, 50));
    mergeSortBtn.setSize(sf::Vector2f(170, 50));
    quickSortBtn.setSize(sf::Vector2f(170, 50));
    heapSortBtn.setSize(sf::Vector2f(170, 50));

    bubbleSortBtn.setFillColor(sf::Color::White);
    bubbleSortBtn.setOutlineThickness(2);
    bubbleSortBtn.setOutlineColor(sf::Color::Black);

    insertionSortBtn.setFillColor(sf::Color::White);
    insertionSortBtn.setOutlineThickness(2);
    insertionSortBtn.setOutlineColor(sf::Color::Black);

    selectionSortBtn.setFillColor(sf::Color::White);
    selectionSortBtn.setOutlineThickness(2);
    selectionSortBtn.setOutlineColor(sf::Color::Black);

    mergeSortBtn.setFillColor(sf::Color::White);
    mergeSortBtn.setOutlineThickness(2);
    mergeSortBtn.setOutlineColor(sf::Color::Black);

    quickSortBtn.setFillColor(sf::Color::White);
    quickSortBtn.setOutlineThickness(2);
    quickSortBtn.setOutlineColor(sf::Color::Black);

    heapSortBtn.setFillColor(sf::Color::White);
    heapSortBtn.setOutlineThickness(2);
    heapSortBtn.setOutlineColor(sf::Color::Black);

    bool sorty = false;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                    if (bubbleSortBtn.getGlobalBounds().contains(mousePosF))
                    {
                        reset();
                        bubbleSort();
                        so.play();
                        drawSorted();
                    }
                    else
                        if (insertionSortBtn.getGlobalBounds().contains(mousePosF))
                    {
                        reset();
                        insertionSort();
                        so.play();
                        drawSorted();
                    }
                    else if (selectionSortBtn.getGlobalBounds().contains(mousePosF))
                    {
                        reset();
                        selectionSort();
                        so.play();
                        drawSorted();
                    }
                    else if (mergeSortBtn.getGlobalBounds().contains(mousePosF))
                    {
                        reset();
                        mergeSort(0, n - 1);
                        so.play();
                        drawSorted();
                    }
                    else if (quickSortBtn.getGlobalBounds().contains(mousePosF))
                    {
                        reset();
                        quickSort(0, n - 1);
                        so.play();
                        drawSorted();
                    }
                    else if (heapSortBtn.getGlobalBounds().contains(mousePosF))
                    {
                        reset();
                        heapSort();
                        so.play();
                        drawSorted();
                    }
                }
            }
        }
        if (!sorty){
            draw(-1, -1, -1, -1, -1);

        }
    }
    return 0;
}
