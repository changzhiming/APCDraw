#include "UndoAddDel.h"

#include <QDebug>

TUndoAddDel::TUndoAddDel() : TUndo()
{
    mOperation = OPERATION_ADD;
}

TUndoAddDel::TUndoAddDel(TScene * Scene, QList<TItem *> &ItemList, QUndoCommand * Parent)
    : TUndo(Scene, ItemList, Parent)
{
}

void TUndoAddDel::undo()
{
    if(OPERATION_ADD == mOperation)
        fDoDel();
    else
        fDoAdd();
}

void TUndoAddDel::redo()
{
    if(OPERATION_ADD == mOperation)
        fDoAdd();
    else
        fDoDel();
}

void TUndoAddDel::fDoAdd()
{
    if(mScene) {
        foreach(TItem *Item, mList)
        {
            mScene->addItem(Item);
        }
    }
}

void TUndoAddDel::fDoDel()
{
    if(mScene) {
        foreach(TItem *Item, mList)
        {
            mScene->removeItem(Item);
        }
    }
}

void TUndoAddDel::fSetOperation(int Operation)
{
    mOperation = Operation;
}

int TUndoAddDel::fGetOperation()
{
    return mOperation;
}
