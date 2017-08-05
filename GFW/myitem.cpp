#include "myitem.h"


int factorial(int n)      //перестановки
{

    if (n >= 0)
    {
        int f = 1;
        for (int i = 2; i <= n; ++i)
        {
            f *= i;
        }
        return f;
    }
    return 0;
}
int allocation(int i, int n)//размещения
{
    int f = 1;
    for (int j = 0; j < i; ++j)
    {
        f *= (n - j);
    }
    return f;
}
int combination(int i, int n) //сочетания
{
     return (allocation(i, n) / factorial(i));
}


MyItem::MyItem(QRectF r):QGraphicsItem(),pixels()
{
    //setFlag(ItemIsMovable);
    //setFlag(ItemIsSelectable);
    setAcceptDrops(true);
    rect=new QRectF(r.topLeft(),r.bottomRight());
    picture=new QImage(boundingRect().width(),boundingRect().height(),QImage::Format_RGB32);
    color=new RGBPIXEL(0,0,255);
    points=new QVector<QPoint>();

}

MyItem::~MyItem()
{
    delete points;
    delete picture;
    delete rect;

}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(boundingRect(),*picture);
    painter->setPen(QPen(Qt::green));
    painter->drawRect(*rect);
    update();
}

QRectF MyItem::boundingRect() const
{
    return QRectF(*rect);
}

void MyItem::advance(int phase)
{
    gfRedrawPicture();
}

void MyItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

}

void MyItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void MyItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{

}
//в этой функции можно делать все что связано с анимацией
void MyItem::gfRedrawPicture()
{

}


void MyItem::SetColor(QColor col)
{
    delete color;
    color=new RGBPIXEL(col.red(),col.green(),col.blue());

}

void MyItem::SavePicture()
{
    picture->save("Screenshot.png");
}

void MyItem::SetDashes(int *pix,int n)
{
    if (pix!=nullptr)
    {
      for(int i=0;i<n;++i)
      {
        pixels.append(pix[i]);
      }
      delete pix;
    }
}

void MyItem::SetObject(int index)
{
    switch (index)
    {
      case 0:
         objtype=LINE;
         break;
      case 1:
         objtype=POLYGON;
         break;
      case 2:
         objtype=SPLINE;
         break;
      case 3:
        objtype=BEZIERCURVE;
        break;
      default:
        objtype=LINE;

    }
}

void MyItem::gfOnLMouseClick(int x, int y)
{

    switch (objtype)
     {
     case LINE:
       ++mc;
         if (mc==1)
         {
           points->append(QPoint(x,y));
           return;
         }
         if (mc==2)
         {
           points->append(QPoint(x,y));
           if (width!=0)
           {
              gfDrawDashedLine(points->at(0).x(),points->at(0).y(),points->at(1).x(),points->at(1).y(),*color,width,linecap,pixels);
              mc=0;
             points->pop_front();
             points->pop_front();
              return;
           }
           if (width!=0)
           {
               gfDrawLine(points->at(0).x(),points->at(0).y(),points->at(1).x(),points->at(1).y(),*color,width,linecap);
               mc=0;
              points->pop_front();
              points->pop_front();
               return;
           }
           gfDrawLine(points->at(0).x(),points->at(0).y(),points->at(1).x(),points->at(1).y(),*color);
           mc=0;
           points->pop_front();
           points->pop_front();
           return;

         }
        break;
     case POLYGON:
         ++mc;
        points->append(QPoint(x,y));
        gfSetPixel(x,y,*color);
        break;
     case SPLINE:

        break;
     default:
        break;
    }

}

void MyItem::gfOnRMouseClick(int x, int y)
{
    switch (objtype)
     {
     case LINE:
        break;
     case POLYGON:
        if(mc>2)
          {
            int* X=new int[mc];
            int* Y=new int[mc];
            for(int i=0;i<mc;++i)
            {
               X[i]=points->at(i).x();
               Y[i]=points->at(i).y();
            }
            gfDrawPolygon(X,Y,mc,*color);
            delete X;
            delete Y;
            for(int i=0;i<mc;++i)
            {
               points->pop_front();
            }
            mc=0;
          }
        else
        {
            for(int i=0;i<mc;++i)
            {
               points->pop_front();
            }
           mc=0;

        }
        break;
     case SPLINE:

        break;
     default:
        mc=0;
        break;
    }
}

void MyItem::gfSetPixel(int x, int y, RGBPIXEL color)
{
    QColor c(color.red,color.green,color.blue);
    picture->setPixel(x,y,c.rgb());
}

void MyItem::gfDrawExample(int index)
{
    //STAR
    int X_STAR[5]={200,250,100,300,150};
    int Y_STAR[5]={100,300,200,200,300};
    switch (index)
    {
       case 0:
           gfDrawPolygon(X_STAR,Y_STAR,5,RGBPIXEL::DkMagenta());//рисуем звезду
           break;
       case 1:
           break;
       default:
           break;
    }

}
void MyItem::gfDrawLine(int x0, int y0, int x1, int y1, RGBPIXEL color)
{

    int d = 0;
    int dy = y1 - y0;
    int dx = x1 - x0;
    if ((x0 < x1) && (y0 < y1))
        {
            if (dy <= dx)
            {
                int y_temp = y0;
                gfSetPixel(x0, y_temp, color);
                for (int i = x0+1; i <= x1; ++i)
                {

                    d += 2 * dy;
                    if (d <= dx)
                        gfSetPixel(i, y_temp, color);
                    else
                    {
                        d -= 2 * dx;
                        y_temp += 1;
                        gfSetPixel(i, y_temp, color);

                    }
                }
                return;
            }
            else
            {
                //dx=t;dx=dy;dy=t;
                int x_temp = x0;
                gfSetPixel(x_temp, y0, color);
                for (int i = y0+1; i <= y1; ++i)
                {
                    d += 2 * dx;
                    if (d < dy)
                        gfSetPixel(x_temp, i, color);
                    else
                    {
                        d -= 2 * dy;
                        x_temp += 1;
                        gfSetPixel(x_temp, i, color);

                    }
                }
                return;
            }
        }
    if (((x0 > x1) && (y0 <= y1)))
        {
            if (dy <= (-1)*dx)
            {
                int y_temp = y1;
                gfSetPixel(x1, y_temp, color);
                for (int i = x1+1; i <= x0; ++i)
                {
                    d += 2 * dy;
                    if (d <= (-1)*dx)
                        gfSetPixel(i, y_temp, color);
                    else
                    {
                        d += 2 * dx;
                        y_temp -= 1;
                        gfSetPixel(i, y_temp, color);

                    }
                }
                return;
            }
            else
            {
                int x_temp = x0;
                gfSetPixel(x_temp, y0, color);
                for (int i = y0+1; i <= y1; ++i)
                {
                    d -= 2 * dx;
                    if (d < dy)
                        gfSetPixel(x_temp, i, color);
                    else
                    {
                        d -= 2 * dy;
                        x_temp -= 1;
                        gfSetPixel(x_temp, i, color);

                    }
                }
                return;
            }
        }
    if ((x0 < x1) && (y0 >= y1))
        {
            if ((-1)*dy <= dx)
            {
                int y_temp = y0;
                gfSetPixel(x0, y_temp, color);
                for (int i = x0+1; i <= x1; ++i)
                {
                    d -= 2 * dy;
                    if (d <= dx)
                        gfSetPixel(i, y_temp, color);
                    else
                    {
                        d -= 2 * dx;
                        y_temp -= 1;
                        gfSetPixel(i, y_temp, color);

                    }
                }
                return;
            }
            else
            {
                int x_temp = x1;
                gfSetPixel(x_temp, y1, color);
                for (int i = y1+1; i <= y0; ++i)
                {
                    d += 2 * dx;
                    if (d <(-1)*dy)
                        gfSetPixel(x_temp,i, color);
                    else
                    {
                        d += 2 * dy;
                        x_temp -= 1;
                        gfSetPixel(x_temp, i, color);

                    }
                }
                return;
            }
        }
    if (((x0 > x1) && (y0 > y1)))
        {
            if (dy >= dx)
            {
                int y_temp = y1;
                gfSetPixel(x1, y_temp, color);
                for (int i = x1+1; i <= x0; ++i)
                {
                    d -= 2 * dy;
                    if (d <= (-1)*dx)
                        gfSetPixel(i, y_temp, color);
                    else
                    {
                        d += 2 * dx;
                        y_temp += 1;
                        gfSetPixel(i, y_temp, color);

                    }
                }
                return;
            }
            else
            {
                int x_temp = x1;
                gfSetPixel(x_temp, y1, color);
                for (int i = y1+1; i <= y0; ++i)
                {
                    d -= 2 * dx;
                    if (d < (-1)*dy)
                        gfSetPixel(x_temp,i, color);
                    else
                    {
                        d += 2 * dy;
                        x_temp+= 1;
                        gfSetPixel(x_temp, i, color);

                    }
                }
                return;
            }
        }
    if ((x0 = x1)&&(y0<=y1))
    {
        for (int i = y0; i <= y1; ++i)
        {
            gfSetPixel(x0, i, color);
        }
        return;
    }
    if ((x0 = x1) && (y0>y1))
    {
        for (int i = y0; i >= y1; --i)
        {
            gfSetPixel(x0, i, color);
        }
        return;
    }
}

void MyItem::gfDrawPolygon(int *X, int *Y, int n, RGBPIXEL color)
{
    for (int i = 0; i < n; ++i)
    {
        gfDrawLine(X[i], Y[i], X[(i + 1) % n], Y[(i + 1) % n],color);
    }
}

bool MyItem::IsConvex(int *X, int *Y, int n)
{
    int cp = 0;
    int ax = 0;
    int ay = 0;
    int bx = 0;
    int by = 0;
    int left = 0;
    int right = 0;
    for (int i = 0; i < n; ++i)
    {
        ax = X[(i + 1) % n] - X[i];
        bx = X[(i + 2) % n] - X[(i + 1) % n];
        ay = Y[(i + 1) % n] - Y[i];
        by = Y[(i + 2) % n] - Y[(i + 1) % n];
        cp = ax*by - ay*bx;
        if (cp > 0)
            ++left;
        if (cp < 0)
            ++right;
    }
    if ((left == 0) || (right == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyItem::IsComplex(int *X, int *Y, int n)
{
    double tab;
        double tcd;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if ((j!=i)&&(j!=(i+1)%n)&&(j!=((i-1+n)%n)))
                {
                    IntersectType type = Cross(X[i], Y[i], X[(i + 1) % n], Y[(i + 1) % n], X[j], Y[j], X[(j + 1) % n], Y[(j + 1) % n], &tab, &tcd);
                        if (type == SKEW_CROSS)
                            return true;
                }
            }
        }
        return false;
}

bool MyItem::PInPolygonEOMode(double x, double y, int *X, int *Y, int n)
{
    int param = 0;
    for (int i = 0; i < n; ++i)
    {
        switch (EdgeType(X[i], Y[i], X[(i + 1) % n], Y[(i + 1) % n], x, y))
        {
        case TOUCHING:
            return true;
        case CROSS_LEFT:
        case CROSS_RIGHT:
            param = 1 - param;
        }
    }
    return param;
}

bool MyItem::PInPolygonNZWMode(double x, double y, int *X, int *Y, int n)
{
    int param = 0;
    for (int i = 0; i < n; ++i)
    {
        switch (EdgeType(X[i], Y[i], X[(i + 1) % n], Y[(i + 1) % n], x, y))
        {
        case TOUCHING:
            return true;
        case CROSS_LEFT:
            ++param;
            break;
        case CROSS_RIGHT:
            --param;
            break;
        }
    }
    return param;
}

void MyItem::gfFillPolygonEOMode(int *X, int *Y, int n, RGBPIXEL color)
{
    int min_X=X[0];
    int min_Y=Y[0];
    int max_X = X[0];
    int max_Y = Y[0];
    for (int i = 0; i < n; ++i)
    {
        if (X[i] < min_X)
        {
            min_X = X[i];
        }
        if (Y[i] < min_Y)
        {
            min_Y = Y[i];
        }
        if (X[i] > max_X)
        {
            max_X = X[i];
        }
        if (Y[i] > max_Y)
        {
            max_Y = Y[i];
        }

    }
    for (int i = min_Y; i <= max_Y; ++i)
    {
        for (int j= min_X; j <=max_X; ++j)
        {
            if (PInPolygonEOMode(j, i, X, Y, n))
            {
                gfSetPixel(j, i, color);
            }
        }
    }
}

void MyItem::gfFillPolygonNZWMode(int *X, int *Y, int n, RGBPIXEL color)
{
    int min_X = X[0];
    int min_Y = Y[0];
    int max_X = X[0];
    int max_Y = Y[0];
    for (int i = 0; i < n; ++i)
    {
        if (X[i] < min_X)
        {
            min_X = X[i];
        }
        if (Y[i] < min_Y)
        {
            min_Y = Y[i];
        }
        if (X[i] > max_X)
        {
            max_X = X[i];
        }
        if (Y[i] > max_Y)
        {
            max_Y = Y[i];
        }

    }
    for (int i = min_Y; i <= max_Y; ++i)
    {
        for (int j = min_X; j <= max_X; ++j)
        {
            if (PInPolygonNZWMode(j, i, X, Y, n))
            {
                gfSetPixel(j, i, color);
            }
        }
    }
}

void MyItem::gfDrawCircle(int x0, int y0, double radius, RGBPIXEL color)
{
    int n = 100;

    int* X=new int[n];
    int* Y=new int[n];
    float* fX = new float[n];
    float* fY = new float[n];
    fX[0] = radius;
    fY[0] = 0;
    float delta = (2 * M_PI / n);
    float cos_d = cosf(delta);
    float sin_d = sinf(delta);

    for (int i = 1; i < n; ++i)
    {
        fX[i]= fX[i - 1] * cos_d - fY[i - 1] * sin_d;
        fY[i] = fX[i - 1] * sin_d + fY[i - 1] * cos_d;
        fX[i - 1] += x0;
        fY[i - 1] += y0;
    }
    fX[n-1] += x0;
    fY[n-1] += y0;
    for (int i = 0; i < n; ++i)
    {
        X[i] = (int)fX[i];
        Y[i] = (int)fY[i];
        if ((fX[i] - X[i])>0.5)
        {
            X[i] += 1;
        }
        if ((fY[i] - Y[i])>0.5)
        {
            Y[i] += 1;
        }
    }


    gfDrawPolygon(X, Y, n, color);
    gfFillPolygonEOMode(X, Y, n, color);
    delete X;
    delete Y;
    delete fX;
    delete fY;
}

void MyItem::gfDrawDashedLine(int x0, int y0, int x1, int y1, RGBPIXEL color, int width, LineCaps captype, const QVector<int> &p)
{

    if (!p.isEmpty())
   {
       float y=y0;
       float x=x0;
       float dx=0;
       float dy=0;
        float cosy = (y1 - y0)/((y1 - y0)^2+(x1 - x0)^2);
        float cosx = (x1 - x0)/((y1 - y0)^2+(x1 - x0)^2);
            if ((x < x1) && (y < y1))
            {
                while((x < x1) && (y < y1))
                {
                for(int i=0;i<p.size();++i)
                {
                   dy=width*cosy*p.at(i);
                   dx=width*cosx*p.at(i);
                  if (!(i%2))
                  {
                      y=y+dy;
                      x=x+dx;
                      if ((y<=y1)&&(x<=x1))
                      {
                         gfDrawLine(x-dx,y-dy,x,y,color,width,FLAT);
                       }
                      else
                      {
                          gfDrawLine(x-dx,y-dy,x1,y1,color,width,captype);
                      }
                  }
                  else
                  {
                      y=y+dy;
                      x=x+dx;

                  }
                }
                }
                 return;
             }
            if ((x > x1) && (y < y1))
                {
                while((x > x1) && (y < y1))
                {
                    for(int i=0;i<p.size();++i)
                    {
                        dy=width*cosy*p.at(i);
                        dx=width*cosx*p.at(i);
                       if (!(i%2))
                       {
                           y=y+dy;
                           x=x-dx;
                           if ((y<=y1)&&(x>=x1))
                           {
                              gfDrawLine(x+dx,y-dy,x,y,color,width,FLAT);
                            }
                           else
                           {
                               gfDrawLine(x+dx,y-dy,x1,y1,color,width,captype);
                           }
                       }
                       else
                       {
                           y=y+dy;
                           x=x-dx;

                       }
                    }
                }
                    return;
                }
            if ((x < x1) && (y > y1))
                {
                while((x < x1) && (y > y1))
                {
                    for(int i=0;i<p.size();++i)
                    {
                        dy=width*cosy*p.at(i);
                        dx=width*cosx*p.at(i);
                       if (!(i%2))
                       {
                           y=y-dy;
                           x=x+dx;
                           if ((y>=y1)&&(x<=x1))
                           {
                              gfDrawLine(x-dx,y+dy,x,y,color,width,FLAT);
                            }
                           else
                           {
                               gfDrawLine(x-dx,y+dy,x1,y1,color,width,captype);
                           }
                       }
                       else
                       {
                           y=y-dy;
                           x=x+dx;

                       }
                    }
                }
                    return;
                }
            if (((x > x1) && (y > y1)))
                {
                while((x > x1) && (y > y1))
                {
                    for(int i=0;i<p.size();++i)
                    {
                        dy=width*cosy*p.at(i);
                        dx=width*cosx*p.at(i);
                       if (!(i%2))
                       {
                           y=y-dy;
                           x=x-dx;
                           if ((y>=y1)&&(x>=x1))
                           {
                              gfDrawLine(x+dx,y+dy,x,y,color,width,FLAT);
                            }
                           else
                           {
                               gfDrawLine(x+dx,y+dy,x1,y1,color,width, captype);
                           }
                       }
                       else
                       {
                           y=y-dy;
                           x=x-dx;

                       }
                    }
                }
                    return;
                }

            if ((x = x1)&&(y<y1))
            {
                while((y<y1))
                {
                    for(int i=0;i<p.size();++i)
                    {
                        dy=width*p.at(i);
                        if (!(i%2))
                        {
                            y=y+dy;
                            if (y<=y1){
                            gfDrawLine(x,y-dy,x,y,color,width,FLAT);
                             }
                            else
                            {
                                gfDrawLine(x,y-dy,x,y1,color,width,captype);
                            }
                        }
                        else
                        {
                            y=y+dy;

                        }
                    }
                }
                    return;
            }
            if ((x = x1) && (y>y1))
            {
                while((y>y1))
                {
                    for(int i=0;i<p.size();++i)
                    {
                        dy=width*p.at(i);
                        if (!(i%2))
                        {
                            y=y-dy;
                            if (y>=y1){
                            gfDrawLine(x,y+dy,x,y,color,width,FLAT);
                             }
                            else
                            {
                                gfDrawLine(x,y+dy,x,y1,color,width,captype);
                            }
                        }
                        else
                        {
                            y=y-dy;

                        }
                    }
                }
                    return;
            }
            if ((x < x1)&&(y=y1))
            {
                while((x<x1))
                {
                    for(int i=0;i<p.size();++i)
                    {
                      dx=width*p.at(i);
                      if (!(i%2))
                      {
                          x=x+dx;
                          if (x<=x1){
                          gfDrawLine(x-dx,y,x,y,color,width,FLAT);
                           }
                          else
                          {
                              gfDrawLine(x-dx,y,x,y1,color,width,captype);
                          }
                      }
                      else
                      {
                          x=x+dx;

                      }
                    }
                }
                    return;
            }
            if ((x> x1) && (y=y1))
            {
                while((x>x1))
                {
                    for(int i=0;i<p.size();++i)
                    {
                        dx=width*p.at(i);
                        if (!(i%2))
                        {
                            x=x-dx;
                            if (x>=x1){
                            gfDrawLine(x+dx,y,x,y,color,width,FLAT);
                             }
                            else
                            {
                                gfDrawLine(x+dx,y,x,y1,color,width,captype);
                            }
                        }
                        else
                        {
                            x=x-dx;

                        }
                    }
                }
                    return;
            }

   }


}


void MyItem::gfDrawLine(int x0, int y0, int x1, int y1, RGBPIXEL color, int width, LineCaps captype)
{

        double length=sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
        int dx = width * (abs(y0 - y1) / length) / 2;
        int dy = width * (abs(x0 - x1)/length)/2;
        int X[] = { x0 - dx, x1 - dx, x1 + dx, x0 + dx };
        int Y[] = { y0 - dy, y1 - dy, y1 + dy, y0 + dy };
        if (((x0 <= x1) && (y0 <= y1)) || ((x0 > x1) && (y0 > y1)))
        {
            X[0] = (x0 - dx);
            X[1] = (x1 - dx);
            X[2] = (x1 + dx);
            X[3] = (x0 + dx);
            Y[0] = (y0 + dy);
            Y[1] = (y1 + dy);
            Y[2] = (y1 - dy);
            Y[3] = (y0 - dy);
         }


        switch (captype)
        {
            case FLAT:
                break;
            case SQUARE:
            X[0] += dy;
            X[1] -= dy;
            X[2] -= dy ;
            X[3] += dy;
            Y[0] -= dx;
            Y[1] += dx;
            Y[2] += dx;
            Y[3] -= dx;
            if (((x0 <= x1) && (y0 <= y1)) || ((x0 > x1) && (y0 > y1)))
            {
                X[0] -= dy;
                X[1] += dy;
                X[2] += dy;
                X[3] -= dy;
                Y[0] -= dx;
                Y[1] += dx;
                Y[2] += dx;
                Y[3] -= dx;
            }
                break;
            case ROUND:
                gfDrawCircle(x0, y0, width / 2,color);
                gfDrawCircle(x1, y1, width / 2,color);
                break;

        }
        gfDrawPolygon(X, Y, 4, color);
        gfFillPolygonEOMode(X, Y, 4, color);

}



void MyItem::gfDrawShell(int *X, int *Y, int n, RGBPIXEL color)
{
    int min_X = X[0];
    int max_X = X[0];
    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        if (X[i] < min_X)
        {
            min_X = X[i];
        }
        if (X[i] > max_X)
        {
            max_X = X[i];
            index = i;
        }

    }

    int i=index;
    float max_cos=-1;
    QVector2D a(0,1);
    QVector2D b;
    for (int j = 0; j < n; ++j)
    {
        if (j != i)
        {

            float sp = ((Y[j] - Y[i]) / sqrtf((X[j] - X[i])*(X[j] - X[i]) + (Y[j] - Y[i])*(Y[j] - Y[i])));
            if (max_cos < sp)
            {
                max_cos = sp;
                index = j;
            }
        }
    }
    b = QVector2D((X[index] - X[i]), (Y[index] - Y[i]));
    b.normalize();
    gfDrawLine(X[i], Y[i], X[index], Y[index], color);
    int k = index;
    max_cos = -1;
    while (k!=i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (j != k)
            {
                float sp = (((X[j]-X[k])*(b.x())+(b.y())*(Y[j] - Y[k])) / sqrtf((X[j] - X[k])*(X[j] - X[k]) + (Y[j] - Y[k])*(Y[j] - Y[k])));
                if (max_cos < sp)
                {
                    max_cos = sp;
                    index = j;
                }
            }
        }
        b = QVector2D((X[index] - X[k]), (Y[index] - Y[k]));
        b.normalize();
        gfDrawLine(X[k], Y[k], X[index], Y[index], color);
        k=index;
        max_cos = -1;

    }
}

void MyItem::gfDrawBezierCurve(int *X, int *Y, int n, RGBPIXEL color)
{
    /*float accuracy = 1000.0;
    int** N = new int*[n+1];
    for (int i = 0; i <= n; ++i)
    {
        N[i] = new int[n+1];
    }
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (i + j <= n)
            {
                N[i][j] = combination(n, j)*combination(n - j, n - i - j)*(pow((-1),(n - i - j)));
            }
            else
                N[i][j] = 0;
        }
    }

    float* T = new float[n + 1];
    for (int i = 0; i <= accuracy; ++i)
    {
        for (int j = 0; j < n + 1;++j)
        {
            T[n-j] = pow(i / accuracy,j);
        }
        float x=0;
        float y=0;
        float* sum = new float[n + 1];
        for (int k = 0; k <= n; ++k)
        {
            for (int l = 0; l <= n; ++l)
            {
                sum[k] += T[l] * N[l][k];
            }
            x += sum[k] * X[k];
            y += sum[k] * Y[k];
        }
        gfSetPixel((int)x,(int) y, color);
        x=0;
        y=0;
        delete[] sum;
    }

    delete[] T;
    for (int i = 0; i <= n; i++) {
        delete[] N[i];
    }
    delete[] N;*/
    float accuracy = 2000.0;
    float x = 0;
    float y = 0;
    float t = 0;
    for (int i = 0; i <= accuracy; ++i)// (i/accuracy) это параметр 0<=t<=1
    {
        t = (float)(i / accuracy);
        for (int j = 0; j < n + 1; ++j)
        {
            x += (combination(j, n))*(pow(t, j))*(pow(1 - t, n - j))*X[j];
            y += (combination(j, n))*(pow(t, j))*(pow(1 - t, n - j))*Y[j];
        }
        gfSetPixel((int)x,(int)y, color);
        x = 0;
        y = 0;
    }
}


void MyItem::gfDrawCubicHermiteSpline(QVector2D *Vertexes, QVector2D *DirectVectors, int n, RGBPIXEL color)
{
    float accuracy = 0.3;
    float* t=new float[n];
    t[0] = 0;
    int x1;
    int y1;
    int x2;
    int y2;
    for (int i = 1; i < n; ++i)
    {
         x1 =(int) Vertexes[i-1].x();
         x2 =(int) Vertexes[i].x();
         y1 =(int) Vertexes[i-1].y();
         y2 =(int) Vertexes[i].y();
        t[i] = sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }
    /*for (int k = 0; k < n-1; ++k)
    {
        float i = 0;
        while( i <= t[k+1])
        {

            float tau = i / t[k + 1];
            float F1k = (2 * tau*tau*tau - 3 * tau*tau + 1);
            float F2k = (3 * tau*tau-2 *tau* tau*tau);
            float F3k = (tau*tau*tau - 2 * tau*tau + tau)*t[k + 1];
            float F4k = tau*(tau*tau - tau)*t[k + 1];
            int x =(int)((F1k*Vertexes[k].x) + (F2k*Vertexes[k + 1].x) + (F3k*DirectVectors[k].x) + (F4k*DirectVectors[k + 1].x));
            int y =(int)((F1k*Vertexes[k].y) + (F2k*Vertexes[k + 1].y) + (F3k*DirectVectors[k].y) + (F4k*DirectVectors[k + 1].y));
            gfSetPixel(x, y, color);
            i += accuracy;

        }
    }*/

    for (int k = 0; k < n - 1; ++k)
    {
        float i =accuracy;
        while (i <= t[k + 1])
        {

            float tau = (i-accuracy) / t[k + 1];
            float F1k = (2 * tau*tau*tau - 3 * tau*tau + 1);
            float F2k = (3 * tau*tau - 2 * tau* tau*tau);
            float F3k = (tau*tau*tau - 2 * tau*tau + tau)*t[k + 1];
            float F4k = tau*(tau*tau - tau)*t[k + 1];
            x1 = (int)((F1k*Vertexes[k].x()) + (F2k*Vertexes[k + 1].x()) + (F3k*DirectVectors[k].x()) + (F4k*DirectVectors[k + 1].x()));
            y1 = (int)((F1k*Vertexes[k].y()) + (F2k*Vertexes[k + 1].y()) + (F3k*DirectVectors[k].y()) + (F4k*DirectVectors[k + 1].y()));
            if ((i == accuracy) && (k!=0))
            {
                gfDrawLine(x2, y2, x1, y1, color);
            }
             tau = (i) / t[k + 1];
            F1k = (2 * tau*tau*tau - 3 * tau*tau + 1);
           F2k = (3 * tau*tau - 2 * tau* tau*tau);
           F3k = (tau*tau*tau - 2 * tau*tau + tau)*t[k + 1];
            F4k = tau*(tau*tau - tau)*t[k + 1];
            x2 = (int)((F1k*Vertexes[k].x()) + (F2k*Vertexes[k + 1].x()) + (F3k*DirectVectors[k].x()) + (F4k*DirectVectors[k + 1].x()));
            y2 = (int)((F1k*Vertexes[k].y()) + (F2k*Vertexes[k + 1].y()) + (F3k*DirectVectors[k].y()) + (F4k*DirectVectors[k + 1].y()));
            i += accuracy;
            gfDrawLine(x1, y1, x2, y2, color);
        }

    }
    delete t;
}


CLPointType MyItem::Classify(double x1, double y1, double x2, double y2, double x, double y)
{
    double ax = x2 - x1;
    double ay = y2 - y1;
    double bx = x - x1;
    double by = y - y1;
    double s = ax*by - bx*ay;
    if (s > 0.0) return LEFT;
    if (s < 0.0) return RIGHT;
    if ((ax*bx < 0.0) || (ay*by < 0.0)) return BEHIND;
    if ((ax*ax + ay*ay) < (bx*bx + by*by)) return BEYOND;
    if ((x1 == x) && (y1 == y)) return ORIGIN;
    if ((x2 == x) && (y2 == y)) return DESTINATION;
}


IntersectType MyItem::Intersect(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double *t)
{
    double nx = dy - cy;
    double ny = cx - dx;
    double denom = nx*(bx - ax) + ny*(by - ay);
    if (denom == 0.0)
    {
        CLPointType type = Classify(cx, cy, dx, dy, ax, ay);
        if ((type == LEFT) || (type == RIGHT))
        {
            return PARALLEL;
        }
        else
            return COLLINEAR;
    }
    double num = nx*(ax - cx) + ny*(ay - cy);
    *t = (-1)*num / denom;
    return SKEW;
}



IntersectType MyItem::Cross(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double *tab, double *tcd)
{
    IntersectType type = Intersect(ax, ay, bx, by, cx, cy, dx, dy, tab);
    if ((type == PARALLEL) || (type == COLLINEAR))
        return type;
    if ((*tab<0.0) || (*tab>1.0))
    {
        return SKEW_NO_CROSS;
    }
    Intersect(cx, cy, dx, dy, ax, ay, bx, by, tcd);
    if ((*tcd<0.0) || (*tcd>1.0))
    {
        return SKEW_NO_CROSS;
    }
    return SKEW_CROSS;
}



EType MyItem::EdgeType(double x0, double y0, double xd, double yd, double xa, double ya)
{
    switch (Classify(x0, y0, xd, yd, xa, ya))
    {
    case LEFT:
        if ((ya > y0) && (ya <= yd))
            return CROSS_LEFT;
        else
            return INESSENTIAL;
    case RIGHT:
        if ((ya > yd) && (ya <= y0))
        {
            return CROSS_RIGHT;
        }
        else return INESSENTIAL;
    case BETWEEN:
    case ORIGIN:
    case DESTINATION:
        return TOUCHING;
    default:
        return INESSENTIAL;
    }
}



void MyItem::gfOnKeyDown(int key)
{
    if (key==Qt::Key_Space)
    {
      //QColor color(255,0,0);
      //picture->setPixel(100,100,color.rgb());
    //  gfDrawLine(40,40,100,100,RGBPIXEL::Green());
    }
    if (key==Qt::Key_F)
    {
        //  gfDrawLine(40,40,100,100,RGBPIXEL::Blue());
    }


}



void MyItem::SetLineCap(int index)
{
    switch (index)
    {
      case 0:
         linecap=FLAT;
         break;
      case 1:
         linecap=ROUND;
         break;
      case 2:
         linecap=SQUARE;
         break;
    }
}



void MyItem::SetLineWidth(int w)
{
    width = w;
}
