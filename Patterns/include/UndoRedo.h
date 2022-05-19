// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include <stack>
#include <memory>

/*
*  Interface for commands executed by the UndoRedoManager
*/
class ICommand
{
public:
	ICommand() {};
	virtual ~ICommand() = default;

	virtual bool Execute() = 0;
	virtual bool Undo() = 0;
	virtual bool Redo() = 0;
};

/*
*
*/
class UndoRedoManager
{
	UndoRedoManager( const UndoRedoManager& ) = delete;
	UndoRedoManager& operator=( const UndoRedoManager& ) = delete;
	UndoRedoManager( UndoRedoManager&& ) = delete;
	UndoRedoManager& operator=( UndoRedoManager&& ) = delete;

public:
	UndoRedoManager() {};
	virtual ~UndoRedoManager() = default;

	/* @brief	Performs execute on the passed command */
	void Exec_Command( ICommand* exec_command );

	/* @brief	Performs undo on the last executed command */
	void Undo_Command();

	/* @brief	Performs a redo on the last undone command */
	void Redo_Command();

protected:
	virtual void OnCommand_Executed( ICommand* exec_command ) = 0;
	virtual void OnCommand_Undone( ICommand* exec_command ) = 0;
	virtual void OnCommand_Redone( ICommand* exec_command ) = 0;

private:
	std::stack<std::unique_ptr<ICommand>> undo_stack;
	std::stack<std::unique_ptr<ICommand>> redo_stack;

};
