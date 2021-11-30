#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

const int ScreenX=18,ScreenY=15;
int movex,movey;

bool invalid[ScreenX][ScreenY];

class Point
{
public:
    int x,y;
};

class Shape
{
public:
    int length;
    vector<Point> points;
    int max_length=0,max_width=0,maxx=0,maxy=0,minx=1e9,miny=1e9;

    void generateShape()
    {
        length = rand()%3+3;
        points.clear();
        points.resize(length);
        max_length=0,max_width=0,maxx=-1e9,maxy=-1e9,minx=1e9,miny=1e9;

        bool up=1,dwn=1,lft=1,rit=1;

        int x=-4,y=0;
        for(int i=0;i<length;i++)
        {
            points[i].x=x;
            points[i].y=y;
            maxx=max(maxx,x);
            maxy=max(maxy,y);
            minx=min(minx,x);
            miny=min(miny,y);

            bool done=0;
            while(!done)
            {

                int dir=rand()%4;
                if(dir==0 && lft)
                {
                    y--;
                    up=lft=dwn=done=1;
                    rit=0;
                }
                else if(dir==1 && rit)
                {
                    y++;
                    dwn=up=rit=done=1;
                    lft=0;
                }
                else if(dir==2 && up)
                {
                    x--;
                    rit=lft=up=done=1;
                    dwn=0;
                }
                else if(dir==3 && dwn)
                {
                    x++;
                    dwn=rit=lft=done=1;
                    up=0;
                }
            }
        }
        max_length = abs(maxx - minx) +1;
        max_width = abs(maxy - miny) +1;

        movex=0,movey=rand()%(ScreenY-max_width)+max_width;

        for(int i=0;i<points.size();i++)
            points[i].x+=movex,points[i].y+=movey;
        maxx+=movex;
        minx+=movex;
        maxy+=movey;
        miny+=movey;

        if(maxy>=ScreenY)
        {
            int tempy=maxy;
            maxy=-1e9,miny=1e9;
            for(int i=0;i<points.size();i++)
                points[i].y-=(tempy-ScreenY+1),maxy=max(maxy,points[i].y),miny=min(miny,points[i].y);
        }
        if(miny<0)
        {
            int tempy=miny;
            maxy=-1e9,miny=1e9;
            for(int i=0;i<points.size();i++)
                points[i].y+=(0-tempy+1),maxy=max(maxy,points[i].y),miny=min(miny,points[i].y);
        }
    }
};

void Rotate(Shape& shape)
{
    vector<Point> rotated = shape.points;

    for(int i=0;i<shape.points.size();i++)
    {
        int tempx=shape.points[i].x;
        int tempy=shape.points[i].y;

        rotated[i].x = shape.minx - (tempy - shape.miny);
        rotated[i].y = shape.miny + (tempx - shape.minx);

        if((rotated[i].x>=0 && invalid[rotated[i].x][rotated[i].y]) || rotated[i].x>=ScreenX || rotated[i].y<0 || rotated[i].y>=ScreenY)
            return;
    }

    for(int i=0;i<shape.points.size();i++)
        shape.points[i] = rotated[i];

    shape.maxx=shape.maxy=0;
    shape.minx=shape.miny=1e9;
    for(int i=0;i<shape.points.size();i++)
    {
        shape.maxx = max(shape.maxx,shape.points[i].x);
        shape.maxy = max(shape.maxy,shape.points[i].y);
        shape.minx = min(shape.minx,shape.points[i].x);
        shape.miny = min(shape.miny,shape.points[i].y);
    }
}

bool Update(Shape& shape)
{
    if(kbhit())
    {
        char in = getch();
        if(in=='a' && shape.miny>=1 && shape.points.size())
        {
            bool not_valid=0;
            for(int i=0;i<shape.points.size();i++)
                if(invalid[shape.points[i].x][shape.points[i].y-1])
                    {not_valid = 1; break;}
            if(!not_valid)
            {
                shape.miny--,shape.maxy--;
                for(int i=0;i<shape.points.size();i++)
                    shape.points[i].y--;
            }
        }
        else if(in=='d' && shape.maxy+1<ScreenY && shape.points.size())
        {
            bool not_valid=0;
            for(int i=0;i<shape.points.size();i++)
                if(invalid[shape.points[i].x][shape.points[i].y+1])
                    {not_valid = 1; break;}

            if(!not_valid)
            {
                shape.maxy++,shape.miny++;
                for(int i=0;i<shape.points.size();i++)
                    shape.points[i].y++;
            }
        }
        else if(in == ' ')
        {
            Rotate(shape);
        }
    }

    bool setShape=0;
    for(int i=0;i<shape.points.size();i++)
    {
        if(shape.points[i].x+1 >= 0 && invalid[shape.points[i].x+1][shape.points[i].y])
        {
            setShape=1;
            break;
        }
    }

    if(shape.maxx==ScreenX-1 || setShape)
    {
        for(int i=0;i<shape.points.size();i++)
            invalid[shape.points[i].x][shape.points[i].y]=1;
        shape.points.clear();
        return 1;
    }

    for(int i=0;i<shape.points.size();i++)
        shape.points[i].x++;
    shape.maxx++,shape.minx++;

    return 0;
}

void Draw(Shape& shape)
{
    for(int i=-5;i<0;i++)
    {
        cout<<"\t ";
        for(int j=0;j<ScreenY;j++)
        {
            bool is_space=1;
            for(int c=0;c<shape.points.size();c++)
            {
                if(i==shape.points[c].x && j==shape.points[c].y)
                {
                    cout<<'0';
                    is_space=0;
                    break;
                }
            }
            if(is_space)
                cout<<' ';
            cout<<' ';
        }
        cout<<"\n";
    }

    for(int i=0;i<ScreenX;i++)
    {
        cout<<"\t#";
        for(int j=0;j<ScreenY;j++)
        {
            if(invalid[i][j])
                cout<<'*';
            else
            {

                bool is_space=1;
                for(int c=0;c<shape.points.size();c++)
                {
                    if(i==shape.points[c].x && j==shape.points[c].y)
                    {
                        cout<<'0';
                        is_space=0;
                        break;
                    }
                }
                if(is_space)
                    cout<<' ';
            }
            cout<<' ';
        }
        cout<<'#';
        cout<<"\n";
    }
    cout<<'\t';
    for(int j=0;j<ScreenY*2+2;j++)
        cout<<'_';
    cout<<"\n";

}

bool lose()
{
    for(int i=0;i<ScreenY;i++)
        if(invalid[0][i])
            return 1;
    return 0;
}

void deleteFullLine()
{
    int del=-1;
    for(int i=1;i<ScreenX;i++)
    {
        int cnt=0;
        for(int j=0;j<ScreenY;j++)
           if(invalid[i][j])
                cnt++;
        if(cnt==ScreenY)
            {del=i;break;}
    }
    if(del!=-1)
    {
        for(int i=del;i>0;i--)
        {
            for(int j=0;j<ScreenY;j++)
               invalid[i][j]=invalid[i-1][j];
        }
    }
}

int main()
{
    srand(time(0));
    Shape shape;
    shape.generateShape();

    Draw(shape);
    system("pause");
    system("cls");

    while(1)
    {
        deleteFullLine();

        Draw(shape);
        if(lose())
        {
            cout<<"GG GAME OVER\n";
            system("pause");
            break;
        }
        if(Update(shape))
            shape.generateShape();

    // TIME PER FRAME
        for(int i=0;i<2e7;i++)
        {}

        system("cls");
    }

    return 0;
}
