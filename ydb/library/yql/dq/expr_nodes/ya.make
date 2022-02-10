LIBRARY() 
 
OWNER( 
    g:yql g:yql_ydb_core
) 
 
SRCS( 
    dq_expr_nodes.h 
) 
 
PEERDIR( 
    ydb/library/yql/core/expr_nodes
) 
 
SRCDIR( 
    ydb/library/yql/core/expr_nodes_gen
) 
 
RUN_PROGRAM( 
    ydb/library/yql/core/expr_nodes_gen/gen
    yql_expr_nodes_gen.jnj 
    dq_expr_nodes.json 
    dq_expr_nodes.gen.h 
    dq_expr_nodes.decl.inl.h 
    dq_expr_nodes.defs.inl.h 
    IN yql_expr_nodes_gen.jnj 
    IN dq_expr_nodes.json 
    OUT dq_expr_nodes.gen.h 
    OUT dq_expr_nodes.decl.inl.h 
    OUT dq_expr_nodes.defs.inl.h 
    OUTPUT_INCLUDES 
    ${ARCADIA_ROOT}/ydb/library/yql/core/expr_nodes_gen/yql_expr_nodes_gen.h
    ${ARCADIA_ROOT}/util/generic/hash_set.h 
) 
 
END()
