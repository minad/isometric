void FUNC(drawPixel)(Surface* s, int x, int y, Uint32 c)
{
    SET(s->getPixels() + s->getPitch() * y + x * BPP, c);
}

void FUNC(drawHLine)(Surface* s, int y, int x1, int x2, Uint32 c)
{
    Uint8* p = s->getPixels() + y * s->getPitch() + x1 * BPP;
    Uint8* pEnd = p + BPP * (x2 - x1);
    while (p <= pEnd)
    {
        SET(p, c);
        p += BPP;
    }
}

void FUNC(drawVLine)(Surface* s, int x, int y1, int y2, Uint32 c)
{
    Uint8* p = s->getPixels() + y1 * s->getPitch() + x * BPP;
    Uint8* pEnd = p + s->getPitch() * (y2 - y1);
    while (p <= pEnd)
    {
        SET(p, c);
        p += s->getPitch();
    }
}

void FUNC(drawLine)(Surface* s, int x1, int y1, int x2, int y2, Uint32 c)
{
    Uint8* p = s->getPixels() + y1 * s->getPitch() + x1 * BPP;
    Uint8* pEnd = p + s->getPitch() * (y2 - y1) + BPP * (x2 - x1);
    
    int xDelta = x2 - x1, yDelta = y2 - y1;
    int xStep = 0, yStep = 0;
    if (xDelta > 0)
        xStep = BPP;
    else if (xDelta < 0)
    {
        xStep = -BPP;
        xDelta = -xDelta;
    }
    
    if (yDelta > 0)
        yStep = s->getPitch();
    else if (yDelta < 0)
    {
        yStep = -s->getPitch();
        yDelta = -yDelta;
    }
    
    int xDelta2 = 2 * xDelta, yDelta2 = 2 * yDelta;
    if (yDelta <= xDelta)
    {
        for (int yDec = yDelta2 - xDelta; ; p += xStep, yDec += yDelta2)
        {
            SET(p, c);
            if (p == pEnd) break;
            if (yDec >= 0)
            {
                yDec -= xDelta2;
                p += yStep;
            }
        }
    }
    else
    {
        for (int xDec = xDelta2 - yDelta; ; p += yStep, xDec += xDelta2)
        {
            SET(p, c);
            if (p == pEnd) break;
            if (xDec >= 0)
            {
                xDec -= yDelta2;
                p += xStep;
            }
        }
    }
}

void FUNC(drawCircle)(Surface* s, int mx, int my, int r, Uint32 c)
{
    Uint8* p = s->getPixels() + my * s->getPitch() + mx * BPP;
    for (int x = 0, y = r, dec = 3 - 2 * r; x <= y; ++x)
    {
        SET(p + x * BPP + y * s->getPitch(), c);
        SET(p + x * BPP - y * s->getPitch(), c);
        SET(p - x * BPP + y * s->getPitch(), c);
        SET(p - x * BPP - y * s->getPitch(), c);
        SET(p + y * BPP + x * s->getPitch(), c);
        SET(p + y * BPP - x * s->getPitch(), c);
        SET(p - y * BPP + x * s->getPitch(), c);
        SET(p - y * BPP - x * s->getPitch(), c);
        if (dec >= 0)
            dec += -4 * --y + 4;
        dec += 4 * x + 6;
    }
}

void FUNC(floodFill)(Surface* s, int x, int y, Uint32 c)
{
    Uint8* p = s->getPixels() + y * s->getPitch() + x * BPP;
    Uint32 fillColor = GET(p);
    
    int lx = x;
    Uint8* lp = p;
    do
    {
        SET(lp, c);
        if (lx == 0)
            break;
        lp -= BPP;
	--lx;
    }
    while (GET(lp) == fillColor);
    
    int rx = x;
    Uint8* rp = p;
    do {
        SET(rp, c);
        if (rx == s->getWidth() - 1)
            break;
        rp += BPP;
	++rx;
    }
    while (GET(rp) == fillColor);
   
    Uint8* tp = lp - s->getPitch();
    Uint8* bp = lp + s->getPitch();
    for (x = lx; x <= rx; ++x)
    {
        if (y - 1 >= 0 && GET(tp) == fillColor)
            FUNC(floodFill)(s, x, y - 1, c);
        if (y + 1 < s->getHeight() && GET(bp) == fillColor)
            FUNC(floodFill)(s, x, y + 1, c);
        tp += BPP;
        bp += BPP;
    }
}

#undef FUNC
#undef BPP
#undef SET
#undef GET
