#pragma once

/// מייצג מהלך יחיד על הלוח
struct Move {
    int fromRow;    
    int fromCol;     
    int toRow;      
    int toCol;      
    bool isCapture; 
    bool isWhite;   
    char symbol;    
};
