import subprocess

# Run the two build commands in the terminal in the current directory
subprocess.run(["clang++", "ExprTool.cpp", "-o", "generate_expr"])
subprocess.run(["clang++", "StmtTool.cpp", "-o", "generate_stmt"])
subprocess.run(["clang++", "ExprVisitorTool.cpp", "-o", "generate_exprVisitor"])

# run the scripts
subprocess.run(["./generate_expr", "../GeneratedHeaders"])
subprocess.run(["./generate_stmt", "../GeneratedHeaders"])
subprocess.run(["./generate_exprVisitor", "../GeneratedHeaders"])