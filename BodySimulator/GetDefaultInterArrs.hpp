#pragma once
#include "Interpreter.hpp"
#include "BaseBody.hpp"

static Interpreter nullCmds;
static Interpreter cellBodyCmds;
static Interpreter foodCellCmds;
static Interpreter wasteCellCmds;
static Interpreter harvesterCellCmds;
static Interpreter predetorCellCmds;
static Interpreter defenderCellCmds;

static void initDefaultInters(); 



Interpreter& getDefaultInters(BaseBody::Type type);


