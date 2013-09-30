#pragma once

#include "Parser/NodeVisitor.h"
#include "Parser/Nodes.h"

// Адаптор для NodeVisitor для использования с managed-кодом.

using namespace System;

namespace FPTL
{
	namespace Runtime
	{
		struct Adapter : public NodeVisitor
		{
			bool (__stdcall *visitEnterASTNode)(ASTNode * );

			bool visitEnter( ASTNode * aNode ) { return false; }

			bool visitEnter( NameRefNode * aNameRefNode ) { return false; }

			bool visitEnter( FunctionNode * aFunctionNode ) { return false; }
	
			/*bool visitEnter( DefinitionNode * aDefinitionNode ) { return mRefVisitor.visitEnter( aDefinitionNode ); }
			
			bool visitEnter( ConstructorNode * aConstructorNode ) { return mRefVisitor.visitEnter( aConstructorNode ); }
			
			bool visitEnter( DataNode * aDataNode ) { return mRefVisitor.visitEnter( aDataNode ); }
			
			bool visitEnter( FunctionalProgram * aFuncProgram ) { return mRefVisitor.visitEnter( aFuncProgram ); }
			
			bool visitEnter( ApplicationBlock * aApplicationBlock ) { return mRefVisitor.visitEnter( aApplicationBlock ); }
			
			bool visitEnter( ExpressionNode * aExpressionNode ) { return mRefVisitor.visitEnter( aExpressionNode ); }
			

			void visitLeave( ASTNode * aNode ) { mRefVisitor.visitLeave( aNode ); }                    
			
			void visitLeave( NameRefNode * aNameRefNode ) { mRefVisitor.visitLeave( aNameRefNode ); }       
			
			void visitLeave( FunctionNode * aFunctionNode ) { mRefVisitor.visitLeave( aFunctionNode ); }
			
			void visitLeave( DefinitionNode * aDefinitionNode ) { mRefVisitor.visitLeave( aDefinitionNode ); }
			
			void visitLeave( ConstructorNode * aConstructorNode ) { mRefVisitor.visitLeave( aConstructorNode ); }
			
			void visitLeave( DataNode * aDataNode ) { mRefVisitor.visitLEave( aDataNode ); }
			
			void visitLeave( FunctionalProgram * aFuncProgram ) { mRefVisitor.visitLeave( aFuncProgram ); }
			
			void visitLeave( ApplicationBlock * aApplicationBlock ) { mRefVisitor.visitLeave( aApplicationBlock ); }
			
			void visitLeave( ExpressionNode * aExpressionNode ) { mRefVisitor.visitLeave( aExpressionNode ); }*/
		};


		ref class RefNodeVisitor
		{
		public:

			bool visitEnter( ASTNode * aNode )
			{
				// Действие по умолчанию.
				return true;
			}
			bool visitEnter( NameRefNode * aNameRefNode )
			{ 
				return redirectVisitEnter(aNameRefNode);
			}
			bool visitEnter( FunctionNode * aFunctionNode )
			{ 
				return redirectVisitEnter(aFunctionNode);
			}
			bool visitEnter( DefinitionNode * aDefinitionNode )   
			{ 
				return redirectVisitEnter(aDefinitionNode);
			}
			bool visitEnter( ConstructorNode * aConstructorNode ) 
			{ 
				return redirectVisitEnter(aConstructorNode);
			}
			bool visitEnter( DataNode * aDataNode )               
			{ 
				return redirectVisitEnter(aDataNode);
			}
			bool visitEnter( FunctionalProgram * aFuncProgram )
			{ 
				return redirectVisitEnter(aFuncProgram);
			}
			bool visitEnter( ApplicationBlock * aApplicationBlock )
			{
				return redirectVisitEnter(aApplicationBlock);
			}
			bool visitEnter( ExpressionNode * aExpressionNode )
			{
				return redirectVisitEnter(aExpressionNode);
			}

			void visitLeave( ASTNode * aNode )                    
			{
				// Действие по умолчанию.
			}
			void visitLeave( NameRefNode * aNameRefNode )        
			{ 
				redirectVisitLeave(aNameRefNode);
			}
			void visitLeave( FunctionNode * aFunctionNode )
			{ 
				redirectVisitLeave(aFunctionNode);
			}
			void visitLeave( DefinitionNode * aDefinitionNode )
			{ 
				redirectVisitLeave(aDefinitionNode);
			}
			void visitLeave( ConstructorNode * aConstructorNode )
			{ 
				redirectVisitLeave(aConstructorNode);
			}
			void visitLeave( DataNode * aDataNode )
			{ 
				redirectVisitLeave(aDataNode);
			}
			void visitLeave( FunctionalProgram * aFuncProgram )
			{ 
				redirectVisitLeave(aFuncProgram);
			}
			void visitLeave( ApplicationBlock * aApplicationBlock )
			{
				redirectVisitLeave(aApplicationBlock);
			}
			void visitLeave( ExpressionNode * aExpressionNode )
			{
				redirectVisitLeave(aExpressionNode);
			}

			delegate bool visitEnterDlg( ASTNode * aNode );

			void process( ASTNode * aNode )
			{
				Adapter adapter;
			}

		private:

			bool redirectVisitEnter( ASTNode * aNode )
			{
				return visitEnter( aNode );
			}
			void redirectVisitLeave( ASTNode * aNode )
			{
				visitLeave( aNode );
			}
		};
	}
}