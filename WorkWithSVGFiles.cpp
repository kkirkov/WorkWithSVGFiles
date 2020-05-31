#include<iostream>
#include<fstream>
#include<string.h>
#include<math.h>
using namespace std;
class Rectangle;
class Circle;
class Line;
///array of labels for all figures
///we use this find out if what we are looking for is:
///1-rectangle
///2-circle
///3-line
int boxOfLabels[30];
///array of all rectangles
Rectangle* boxOfRectangles[10];
///array of all circles
Circle* boxOfCircles[10];
///array of all lines
Line* boxOfLines[10];
///number of all figures
int numberOfObj = 0;
///number of all rectangles
int numberOfRects = 0;
///number of all circles
int numberOfCircles = 0;
///number of all lines
int numberOfLines = 0;

///holds the information of a rectangle
class Rectangle
{
    public:
    int x;
    int y;
    int height;
    int width;
    string colorFill;
    Rectangle(int x, int y, int width, int height, string colorFill)
    {
        this->x = x;
        this->y = y;
        this->height = height;
        this->width = width;
        this->colorFill = colorFill;
        boxOfRectangles[numberOfRects] = this;
        numberOfRects++;
        boxOfLabels[numberOfObj] = 1;
        numberOfObj++;
        cout<<"Successfully created rectangle ("<<numberOfObj<<")"<<endl;
    }
    ~Rectangle()
    {
        numberOfRects--;
        numberOfObj--;
    }
};
///holds the information of a circle
class Circle
{
    private:
    public:
    int cx;
    int cy;
    int r;
    string colorFill;
    Circle(int cx, int cy, int r, string colorFill)
    {
        this->cx = cx;
        this->cy = cy;
        this->r = r;
        this->colorFill = colorFill;
        boxOfCircles[numberOfCircles] = this;
        numberOfCircles++;
        boxOfLabels[numberOfObj] = 2;
        numberOfObj++;
        cout<<"Successfully created circle ("<<numberOfObj<<")"<<endl;
    }
    ~Circle()
    {
        numberOfCircles--;
        numberOfObj--;
    }
};
///holds the information of a line
class Line
{
    private:
    public:
    int x1;
    int y1;
    int x2;
    int y2;
    string colorFill;
    Line(int x1, int y1, int x2, int y2, string colorFill)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->colorFill = colorFill;
        boxOfLines[numberOfLines] = this;
        numberOfLines++;
        boxOfLabels[numberOfObj] = 3;
        numberOfObj++;
        cout<<"Successfully created line ("<<numberOfObj<<")"<<endl;
    }
    ~Line()
    {
        numberOfLines--;
        numberOfObj--;
    }
};
///prepares the arrays
void FillContainersWithNulls()
{
    for(int i=0;i<10;i++)
    {
        boxOfRectangles[i] = nullptr;
        boxOfCircles[i] = nullptr;
        boxOfLines[i] = nullptr;
    }
    for(int i=0;i<30;i++)
    {
        boxOfLabels[i]=0;
    }
}
///save the figures in a file
void SaveFile(string filename)
{
    ofstream file;
    file.open(filename);
    if(file.is_open())
    {//<?xml version="1.0" standalone="no"?>
        file<<"<?xml version=\"1.0\" standalone=\"no\"?>"<<endl;
        file<<"<svg width=\"12cm\" height=\"4cm\" viewBox=\"0 0 1200 400\""<<endl;
        file<<"     xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"<<endl;
        int rectsSofar = 0;
        int circlesSoFar = 0;
        int linesSoFar = 0;
        for(int i=0;i<numberOfObj;i++)
        {
            switch(boxOfLabels[i])
            {
            case 1:
            file<<"<rect x=\""<<boxOfRectangles[rectsSofar]->x<<"\" y=\""<<boxOfRectangles[rectsSofar]->y<<"\" width=\""<<boxOfRectangles[rectsSofar]->width;
            file<<"\" height=\""<<boxOfRectangles[rectsSofar]->height<<"\" fill=\""<<boxOfRectangles[rectsSofar]->colorFill<<"\" />"<<endl;
            rectsSofar++;
            break;
            case 2:
            file<<"<circle cx=\""<<boxOfCircles[circlesSoFar]->cx<<"\" cy=\""<<boxOfCircles[circlesSoFar]->cy;
            file<<"\" r=\""<<boxOfCircles[circlesSoFar]->r<<"\" fill=\""<<boxOfCircles[circlesSoFar]->colorFill<<"\" />"<<endl;
            circlesSoFar++;
            break;
            case 3:
            file<<"<line x1=\""<<boxOfLines[linesSoFar]->x1<<"\" y1=\""<<boxOfLines[linesSoFar]->y1<<"\" x2=\""<<boxOfLines[linesSoFar]->x2;
            file<<"\" y2=\""<<boxOfLines[linesSoFar]->y2<<"\" stroke=\""<<boxOfLines[linesSoFar]->colorFill<<"\" />"<<endl;
            linesSoFar++;
            break;
            }
        }
        file<<"</svg>";
        file.close();
    }
    cout<<"Successfully saved the changes to "<<filename<<endl;
}
///loads figures from a file
void ReadFile(string fileName)
{
    ifstream file(fileName);
    string label;
    char trash;
    getline(file,label);
    getline(file,label);
    getline(file,label);
    while(true)
    {
            file>>trash;
            file>>label;
            if(label=="rect")
            {
                int x;
                int y;
                int height;
                int width;
                string color;
                for(int i=0;i<3;i++)
                {
                    file>>trash;
                }
                file>>x;
                for(int i=0;i<4;i++)
                {
                    file>>trash;
                }
                file>>y;
                for(int i=0;i<8;i++)
                {
                    file>>trash;
                }
                file>>width;
                for(int i=0;i<9;i++)
                {
                    file>>trash;
                }
                file>>height;
                for(int i=0;i<7;i++)
                {
                    file>>trash;
                }
                file>>color;
                color.resize(color.size()-1);
                Rectangle* newRect = new Rectangle(x,y,width,height,color);
                getline(file,label);
            }else if(label=="circle")
            {
                int cx;
                int cy;
                int r;
                string color;
                for(int i=0;i<4;i++)
                {
                    file>>trash;
                }
                file>>cx;
                for(int i=0;i<5;i++)
                {
                    file>>trash;
                }
                file>>cy;
                for(int i=0;i<4;i++)
                {
                    file>>trash;
                }
                file>>r;
                for(int i=0;i<7;i++)
                {
                    file>>trash;
                }
                file>>color;
                color.resize(color.size()-1);
                Circle* newCircle = new Circle(cx,cy,r,color);
                getline(file,label);
            }else if(label=="line")
            {
                int x1;
                int y1;
                int x2;
                int y2;
                string color;
                for(int i=0;i<4;i++)
                {
                    file>>trash;
                }
                file>>x1;
                for(int i=0;i<5;i++)
                {
                    file>>trash;
                }
                file>>y1;
                for(int i=0;i<5;i++)
                {
                    file>>trash;
                }
                file>>x2;
                for(int i=0;i<5;i++)
                {
                    file>>trash;
                }
                file>>y2;
                for(int i=0;i<9;i++)
                {
                    file>>trash;
                }
                file>>color;
                color.resize(color.size()-1);
                Line* newLine = new Line(x1,y2,x2,y2,color);
                getline(file,label);
            }else if(label=="/svg>")
            {
                return;
            }else
            {
                cout<<"Something wrong with that file!"<<endl;
                return;
            }
    }
}
///finds a figure by its number
///this function counts how many labels with the same label are there in the label array before our item
int CountTheObjOfThisKindBeforeOurs(int number)
{
    int counter = 0;
    for(int i=0;i<number;i++)
    {
        if(boxOfLabels[number]==boxOfLabels[i])
        {
            counter++;
        }
    }
    return counter;
}
///Printing the properties of a rectangle
void PrintRect(Rectangle* rect)
{
    cout<<"rectangle "<<rect->x<<" "<<rect->y<<" "<<rect->width<<" "<<rect->height<<" "<<rect->colorFill<<endl;
}
///Printing the properties of a circle
void PrintCircle(Circle* circle)
{
    cout<<"circle "<<circle->cx<<" "<<circle->cy<<" "<<circle->r<<" "<<circle->colorFill<<endl;
}
///Printing the properties of a line
void PrintLine(Line* l)
{
    cout<<"line "<<l->x1<<" "<<l->y1<<" "<<l->x2<<" "<<l->y2<<" "<<l->colorFill<<endl;
}
///Printing the properties of all figures
void PrintAll()
{
    for(int i=0;i<numberOfObj;i++)
    {
        int place = CountTheObjOfThisKindBeforeOurs(i);
        cout<<i+1<<". ";
        if(boxOfLabels[i]==1)
        {
            PrintRect(boxOfRectangles[place]);
        }
        if(boxOfLabels[i]==2)
        {
            PrintCircle(boxOfCircles[place]);
        }
        if(boxOfLabels[i]==3)
        {
            PrintLine(boxOfLines[place]);
        }
    }
}
///erases a figure by its order number
void Erase(int num)
{
    int place = CountTheObjOfThisKindBeforeOurs(num);
    switch(boxOfLabels[num])
    {
        case 0:
        cout<<"There is no figure number "<<num+1<<"!"<<endl;
        break;
        case 1:{
        int i = place;
        delete boxOfRectangles[place];
        boxOfRectangles[i] = boxOfRectangles[i+1];
        i++;
        while(boxOfRectangles[i]!=nullptr)
        {
            boxOfRectangles[i] = boxOfRectangles[i+1];
            i++;
        }
        cout<<"Erased a rectangle ("<<num+1<<")"<<endl;
        break;
        }
        case 2:{
        int i = place;
        delete boxOfCircles[place];
        boxOfCircles[i] = boxOfCircles[i+1];
        i++;
        while(boxOfCircles[i]!=nullptr)
        {
            boxOfCircles[i] = boxOfCircles[i+1];
            i++;
        }
        cout<<"Erased a circle ("<<num+1<<")"<<endl;
        break;
        }
        case 3:{
        int i = place;
        delete boxOfLines[place];
        boxOfLines[i] = boxOfLines[i+1];
        i++;
        while(boxOfLines[i]!=nullptr)
        {
            boxOfLines[i] = boxOfLines[i+1];
            i++;
        }
        cout<<"Erased a line ("<<num+1<<")"<<endl;
        break;
        }
    }
    while(boxOfLabels[num]!=0)
    {
        boxOfLabels[num] = boxOfLabels[num+1];
        num++;
    }

}
///translates all figures
///translates all figures in horizontal direction by a given number
///translates all figures in vertical direction by a given number
void Translate(int trX,int trY)
{
    for(int i=0;i<numberOfRects;i++)
    {
        boxOfRectangles[i]->x += trX;
        boxOfRectangles[i]->y += trY;
    }
    for(int i=0;i<numberOfCircles;i++)
    {
        boxOfCircles[i]->cx += trX;
        boxOfCircles[i]->cy += trY;
    }
    for(int i=0;i<numberOfLines;i++)
    {
        boxOfLines[i]->x1 += trX;
        boxOfLines[i]->y1 += trY;
        boxOfLines[i]->x2 += trX;
        boxOfLines[i]->y2 += trY;
    }
    cout<<"Translated all figures"<<endl;
}
///translates a figure
///translates a figure in horizontal direction by a given number
///translates a figure in vertical direction by a given number
void Translate(int num, int trX, int trY)
{
    int place = CountTheObjOfThisKindBeforeOurs(num);
    switch(boxOfLabels[num])
    {
    case 1:
        boxOfRectangles[place]->x+=trX;
        boxOfRectangles[place]->y+=trY;
        cout<<"Translated a rectangle ("<<num<<")"<<endl;
        break;
    case 2:
        boxOfCircles[place]->cx+=trX;
        boxOfCircles[place]->cy+=trY;
        cout<<"Translated a circle ("<<num<<")"<<endl;
        break;
    case 3:
        boxOfLines[place]->x1+=trX;
        boxOfLines[place]->y1+=trY;
        boxOfLines[place]->x2+=trX;
        boxOfLines[place]->y2+=trY;
        cout<<"Translated a line ("<<num<<")"<<endl;
        break;
    }
}
///finds out all figures in a given rectangle
void WithinRect(int x, int y, int width, int height)
{
    for(int i=0;i<numberOfObj;i++)
    {
        int place = CountTheObjOfThisKindBeforeOurs(i);
        switch(boxOfLabels[i])
        {
        case 1:
            if(boxOfRectangles[place]->x>=x&&boxOfRectangles[place]->y>=y&&(boxOfRectangles[place]->x+boxOfRectangles[place]->width)<=x+width&&(boxOfRectangles[place]->y+boxOfRectangles[place]->height)<=y+height)
            {
                cout<<i<<". ";
                PrintRect(boxOfRectangles[place]);
            }
            break;
        case 2:
            if((boxOfCircles[place]->cx-boxOfCircles[place]->r)>=x&&(boxOfCircles[place]->cy-boxOfCircles[place]->r)>=y)
            {
                if((boxOfCircles[place]->cx+boxOfCircles[place]->r)<=x+width&&(boxOfCircles[place]->cy+boxOfCircles[place]->r)<=y+height)
                {
                    cout<<i<<". ";
                    PrintCircle(boxOfCircles[place]);
                }
            }
            break;
        case 3:
            if(boxOfLines[place]->x1<=x&&boxOfLines[place]->x1>=x+width&&boxOfLines[place]->x2<=x&&boxOfLines[place]->x2>=x+width)
            {
                if(boxOfLines[place]->y1<=y&&boxOfLines[place]->y1>=y+height&&boxOfLines[place]->y2<=y&&boxOfLines[place]->y2>=y+height)
                {
                    cout<<i<<". ";
                    PrintLine(boxOfLines[place]);
                }
            }
        }

    }
}
///finds out all figures in a given circle
void WithinCircle(int cx, int cy, int r)
{
    for(int i=0;i<numberOfObj;i++)
    {
        int place = CountTheObjOfThisKindBeforeOurs(i);
        switch(boxOfLabels[i])
        {
        case 1:
            if(sqrt(pow(cx-boxOfRectangles[place]->x,2) + pow(cy-boxOfRectangles[place]->y,2))<=r)
            {
                if(sqrt(pow(boxOfRectangles[place]->x+boxOfRectangles[place]->width-cx,2) + pow(cy-boxOfRectangles[place]->y,2))<=r)
                {
                    if(sqrt(pow(boxOfRectangles[place]->x+boxOfRectangles[place]->width-cx,2) + pow(boxOfRectangles[place]->y+boxOfRectangles[place]->height-cy,2)<=r))
                    {
                        if(sqrt(pow(cx-boxOfRectangles[place]->x,2) + pow(boxOfRectangles[place]->y+boxOfRectangles[place]->height-cy,2)<=r))
                        {
                            cout<<i<<". ";
                            PrintRect(boxOfRectangles[place]);
                        }
                    }
                }
            }
            break;
        case 2:
            if(boxOfCircles[place]->cy-boxOfCircles[place]->r>=cy-r&&boxOfCircles[place]->cy+boxOfCircles[place]->r<=cy+r)
            {
                if(boxOfCircles[place]->cx-boxOfCircles[place]->r>=cx-r&&boxOfCircles[place]->cx+boxOfCircles[place]->r<=cx+r)
                {
                    cout<<i<<". ";
                    PrintCircle(boxOfCircles[place]);
                }
            }
            break;
        case 3:
            if(sqrt(pow(cx-boxOfLines[place]->x1,2) + pow(cy-boxOfLines[place]->y1,2))<=r)
            {
                if(sqrt(pow(cx-boxOfLines[place]->x2,2) + pow(cy-boxOfLines[place]->y2,2))<=r)
                {
                    cout<<i<<". ";
                    PrintLine(boxOfLines[place]);
                }
            }
            break;
        }
    }
}

int main()
{
FillContainersWithNulls();
string command;
string fileName;
cin>>command;
while(command!="exit")
{
    if(command=="open")
    {
        cin>>fileName;
        ReadFile(fileName);
    }else if(command=="close")
    {
        cout<<endl;
        cin>>command;
        if(command=="open")
        {
        cin>>fileName;
        ReadFile(fileName);
        }else return 0;

    }else if(command=="save")
    {
        SaveFile(fileName);
    }else if(command=="saveas")
    {
        string name;
        cin>>name;
        SaveFile(name);
    }else if(command=="help")
    {
            cout<<"open <file>	  opens <file>"<<endl;
            cout<<"close		  closes currently opened file"<<endl;
            cout<<"save			  saves the currently open file"<<endl;
            cout<<"saveas <file>  saves the currently open file in <file>"<<endl;
            cout<<"help			  prints this information"<<endl;
            cout<<"exit			  exists the program"<<endl;
            cout<<"print          prints all figure"<<endl;
            cout<<"create         creates a new figure"<<endl;
            cout<<"erase          remove a figure"<<endl;
            cout<<"translate      translates a figure"<<endl;
            cout<<"translateall  translates all figures"<<endl;
            cout<<"within         prints all figures within a figure"<<endl;
    }else if(command=="print")
    {
        PrintAll();
    }else if(command=="create")
    {
        string type;
        int x;
        int y;
        string color;
        cin>>type;
        if(type=="rectangle")
        {
            int width;
            int height;
            cin>>x>>y>>width>>height>>color;
            Rectangle* newRect = new Rectangle(x,y,width,height,color);
        }else if(type=="circle")
        {
            int r;
            cin>>x>>y>>r>>color;
            Circle* newCircle = new Circle(x,y,r,color);
        }else if(type=="line")
        {
            int x2;
            int y2;
            cin>>x>>y>>x2>>y2>>color;
            Line* newLine = new Line(x,y,x2,y2,color);
        }else cout<<"Wrong type of figure!"<<endl;
    }else if(command=="erase")
    {
        int num;
        cin>>num;
        Erase(num-1);
    }else if(command=="translate")
    {
        int num;
        cin>>num;
        int trX;
        int trY;
        cout<<" horizontal=";
        cin>>trX;
        cout<<" vertical=";
        cin>>trY;
        Translate(num,trX,trY);
    }else if(command=="translateall")
    {
        int trX;
        int trY;
        cout<<" horizontal=";
        cin>>trX;
        cout<<" vertical=";
        cin>>trY;
        Translate(trX,trY);
    }else if(command=="within")
    {
        string option;
        cin>>option;
        if(option=="circle")
        {
            int cx;
            int cy;
            int r;
            cin>>cx>>cy>>r;
            WithinCircle(cx,cy,r);
        }else if(option=="rectangle")
        {
            int x;
            int y;
            int width;
            int height;
            cin>>x>>y>>width>>height;
            WithinRect(x,y,width,height);
        }
    }
    cin>>command;
}
cout<<"Exit"<<endl;
}
