// MIT License, Copyright (c) 2022 Malik Allen

#include "../include/UndoRedo.h"

void UndoRedoManager::Exec_Command( ICommand* exec_command )
{
	std::unique_ptr<ICommand> command = std::make_unique<ICommand>( exec_command );
	if( command.get() )
	{
		redo_stack.empty();
		command->Execute();
		OnCommand_Executed( command.get() );
		undo_stack.push( command );
	}
}

void UndoRedoManager::Undo_Command()
{
	if( undo_stack.size() <= 0 )
		return;
	undo_stack.top()->Undo();
	OnCommand_Undone( undo_stack.top().get() );
	redo_stack.push( undo_stack.top() );
	undo_stack.pop();
}

void UndoRedoManager::Redo_Command()
{
	if( redo_stack.size() <= 0 )
		return;
	redo_stack.top()->Redo();
	OnCommand_Redone( redo_stack.top().get() );
	undo_stack.push( redo_stack.top() );
	redo_stack.pop();
}