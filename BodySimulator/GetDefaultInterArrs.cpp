#include "GetDefaultInterArrs.hpp"

void initDefaultInters()
{
	nullCmds.pushCmd(Interpreter::C_EMPTY, Interpreter::A_EMPTY);

	cellBodyCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_FOOD);
	cellBodyCmds.pushCmd(Interpreter::C_MOVEOUT, Interpreter::A_WASTE);
	cellBodyCmds.pushCmd(Interpreter::C_REPAIR, Interpreter::A_HULL);
	cellBodyCmds.pushCmd(Interpreter::C_REPLICATE, Interpreter::A_EGG);
	cellBodyCmds.pushCmd(Interpreter::C_MOVEOUT, Interpreter::A_EGG);

	foodCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_SUN);
	foodCellCmds.pushCmd(Interpreter::C_REPAIR, Interpreter::A_HULL);
	foodCellCmds.pushCmd(Interpreter::C_REPLICATE, Interpreter::A_EGG);
	foodCellCmds.pushCmd(Interpreter::C_MOVEOUT, Interpreter::A_EGG);

	wasteCellCmds.pushCmd(Interpreter::C_MOVEIN, Interpreter::A_FOOD);
	wasteCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_FOOD);
	wasteCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_WASTE);
	wasteCellCmds.pushCmd(Interpreter::C_MOVEIN, Interpreter::A_WASTE);
	wasteCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_WASTE);
	wasteCellCmds.pushCmd(Interpreter::C_MOVEIN, Interpreter::A_WASTE);
	wasteCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_WASTE);
	wasteCellCmds.pushCmd(Interpreter::C_MOVEIN, Interpreter::A_WASTE);
	wasteCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_WASTE);
	wasteCellCmds.pushCmd(Interpreter::C_REPAIR, Interpreter::A_HULL);
	wasteCellCmds.pushCmd(Interpreter::C_REPLICATE, Interpreter::A_EGG);
	wasteCellCmds.pushCmd(Interpreter::C_MOVEOUT, Interpreter::A_EGG);

	harvesterCellCmds.pushCmd(Interpreter::C_WRITE_POS, Interpreter::A_NEAREST_CORPSE);
	harvesterCellCmds.pushCmd(Interpreter::C_MOVE, Interpreter::A_POS);
	harvesterCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_NEAREST_CORPSE);
	
	predetorCellCmds.pushCmd(Interpreter::C_WRITE_POS, Interpreter::A_NEAREST_STATIC);
	predetorCellCmds.pushCmd(Interpreter::C_MOVE, Interpreter::A_POS);
	predetorCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_NEAREST_STATIC);

	defenderCellCmds.pushCmd(Interpreter::C_WRITE_POS, Interpreter::A_NEAREST_ENEMIE);
	defenderCellCmds.pushCmd(Interpreter::C_MOVE, Interpreter::A_POS);
	defenderCellCmds.pushCmd(Interpreter::C_CONSUME, Interpreter::A_NEAREST_ENEMIE);
	defenderCellCmds.pushCmd(Interpreter::C_EMPTY, Interpreter::A_EMPTY);
}

Interpreter & getDefaultInters(BaseBody::Type type)
{
	static bool hasBeenInit = false;
	if (hasBeenInit == false) {
		initDefaultInters();
		hasBeenInit = true;
	}

	switch (type) {
	case BaseBody::T_CELL:
		return cellBodyCmds;
		break;
	case BaseBody::T_FOODCELL:
		return foodCellCmds;
		break;
	case BaseBody::T_WASTECELL:
		return wasteCellCmds;
		break;
	case BaseBody::T_HARVESTERCELL:
		return harvesterCellCmds;
		break;
	case BaseBody::T_PREDATORCELL:
		return predetorCellCmds;
		break;
	case BaseBody::T_DEFENDERCELL:
		return defenderCellCmds;
		break;
	default:
		break;
	}


	return nullCmds;
}
