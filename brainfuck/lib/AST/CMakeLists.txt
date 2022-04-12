add_library(ExprAST ExprAST.cpp)

target_link_libraries(ExprAST PUBLIC ${llvm_libs})
