#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

int points=0,limit=0;

void draw(char scr[22][15])
{

    cout<<"\n";
    for(int i=6;i<22;i++)
    {
        cout<<"# ";
        for(int j=0;j<15;j++)
            cout<<scr[i][j]<<" ";
        cout<<"#\n";
    }
        for(int j=0;j<17;j++)
            cout<<"_ ";
        cout<<"\n\n\t POINTS: "<<points<<"\n";
}

void set_zero(char scr[22][15])
{
    for(int i=21;i>=0;i--)
    {
        for(int j=0;j<15;j++)
        {
            if(scr[i][j]=='0')
                scr[i][j]='*';
        }
    }
    cout<<"\a";
}

bool apply_gravity(char scr[22][15])
{
    for(int i=20;i>=0;i--)
    {
        for(int j=0;j<15;j++)
        {
            if(scr[21][j]=='0' || (scr[i+1][j]=='*' && scr[i][j]=='0'))
                return 1;
        }
    }

    for(int i=20;i>=0;i--)
    {
        for(int j=0;j<15;j++)
        {
            if(scr[i+1][j]==' ' && scr[i][j]=='0')
                swap(scr[i+1][j],scr[i][j]);
        }
    }

    return 0;
}


void rotatee(char scr[22][15])
{
    int mnx=INT_MAX,mny=INT_MAX,mxx=INT_MIN,mxy=INT_MIN;
    for(int i=6;i<22;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(scr[i][j]=='0')
            {
                mnx=min(mnx,i);
                mny=min(mny,j);
                mxx=max(mxx,i);
                mxy=max(mxy,j);

               // mnx=mxx-2;
               // mny=mxy-2;

            }
        }
    }

    // if(mxx-mny+mnx>21 || mxy-mnx+mny>14 )
   //    return;

    vector<pair<int,int>> v;
    for(int rs=6;rs<22;rs++)
    {
        for(int cs=0;cs<15;cs++)
        {
            int x=0,y=0;
            pair<int,int> pt;
            if(scr[rs][cs]=='0')
            {

                scr[rs][cs]='D';
                //x=cs-mny+mnx+1;
                //else
                x=cs-mny+mnx;
                y=rs-mnx+mny;
                //if(cs>mny+1 && limit==4)
                //y++;

                //swap(scr[i][j],scr[x][y]);

                pt.first=x;
                pt.second=y;
                v.push_back(pt);
                //scr[x][y]='F';

            }
        }
    }

    for(int i=0;i<v.size();i++)
                {
                   // cout<<v[i].first<<" "<<v[i].second<<endl;

                    scr[v[i].first][v[i].second]='0';



                }

    for(int rs=6;rs<22;rs++)
    {
        for(int cs=0;cs<15;cs++)
        {
            if(scr[rs][cs]=='D')
            {
                scr[rs][cs]=' ';
            }
        }
    }

    v.clear();

}


void input(char scr[22][15])
{
    if(kbhit())
    {
        char in=getch();
        if(in=='a')
        {
            for(int i=21;i>=0;i--)
            {
                for(int j=1;j<15;j++)
                {
                    if(scr[i][j]=='0')
                    {
                        if(scr[i][j-1]=='*' || scr[i][0]=='0')
                            return;
                    }
                }
            }


            for(int i=21;i>=0;i--)
            {
                for(int j=1;j<15;j++)
                {
                    if(scr[i][j]=='0')
                    {
                        if(scr[i][j-1]==' ')
                            swap(scr[i][j-1],scr[i][j]);
                    }
                }
            }
        }
        else if(in=='d')
        {
            for(int i=21;i>=0;i--)
            {
                for(int j=13;j>=0;j--)
                {
                    if(scr[i][j]=='0')
                    {
                        if(scr[i][j+1]=='*' || scr[i][14]=='0')
                            return;
                    }
                }
            }

            for(int i=21;i>=0;i--)
            {
                for(int j=13;j>=0;j--)
                {
                    if(scr[i][j]=='0')
                    {
                        if(scr[i][j+1]==' ')
                            swap(scr[i][j+1],scr[i][j]);
                    }
                }
            }
        }
        else if(in==' ')
            {
                rotatee(scr);
                system("cls");
                draw(scr);
            }
    }

}

bool check_win_lose(char scr[22][15])
{

    for(int j=0;j<15;j++)
    {
        if(scr[6][j]=='*')
            return 0;
    }
    for(int i=7;i<22;i++)
    {
        int c=0;
        for(int j=0;j<15;j++)
        {
            if(scr[i][j]=='*')
                c++;
        }
        if(c==15)
        {
            points+=5;
            for(int j=i;j>0;j--)
            {
                swap(scr[j],scr[j-1]);
            }
            apply_gravity(scr);
        }
    }
    return 1;
}

void generate_block(char scr[22][15])
{
    int decsn,cnt=0;
    int x=4,y=7;

//-----------------------------------
    bool b1=1,b2=1,b3=1,b4=1;
//-----------------------------------

    limit=rand()%2+4;
    while(cnt<limit)
    {
         decsn=rand()%4;
         if(decsn==0 && b1)
         {
             x++;
             scr[x][y]='0';
             b2=0;
             b1=1,b3=1,b4=1;
             cnt++;
         }
         else if(decsn==1 && b2)
         {
             x--;
             scr[x][y]='0';
             b1=0;
             b2=1,b3=1,b4=1;
             cnt++;
         }
         else if(decsn==2 && b3)
         {
             y++;
             scr[x][y]='0';
             b4=0;
             b2=1,b3=1,b1=1;
             cnt++;
         }
         else if(decsn==3 && b4)
         {
             y--;
             scr[x][y]='0';
             b3=0;
             b2=1,b4=1,b1=1;
             cnt++;
         }
    }

}


int main()
{
    int rows=22,columns=15;
    char screen[22][15];
    srand(time(0));

    for(int i=0;i<22;i++)
    {
        for(int j=0;j<15;j++)
            screen[i][j]=' ';
    }
    generate_block(screen);

    while(1)
    {
        draw(screen);
        if(apply_gravity(screen))
            {
                set_zero(screen);
                generate_block(screen);
            }
        input(screen);
        if(check_win_lose(screen)==0)
            return 0;
        system("cls");
        draw(screen);
        for(int i=0;i<55000000;i++){}
        system("cls");

    }

    return 0;
}
