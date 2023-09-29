#include "helper.h"

#include <ydb/core/grpc_services/local_rpc/local_rpc.h>
#include <ydb/library/yql/public/issue/yql_issue_message.h>
#include <ydb/library/ydb_issue/issue_helpers.h>

namespace NKikimr {

namespace NGRpcService {

IActor* CreatePgAlterTableRpcActor(NKikimr::NGRpcService::IRequestOpCtx* msg);

using TEvAlterTableRequest = NGRpcService::TGrpcRequestOperationCall<Ydb::Table::AlterTableRequest,
    Ydb::Table::AlterTableResponse>;

struct TEvPgAlterTableRequest : public TEvAlterTableRequest {
    static IActor* CreateRpcActor(IRequestOpCtx* msg) {
        return CreatePgAlterTableRpcActor(msg);
    }
};

} // NGRpcService

namespace NKqp {

using namespace NYql;
using namespace Ydb;

IKikimrGateway::TGenericResult GenericResultFromSyncOperation(const Operations::Operation& op) {
    using NYql::NCommon::ResultFromIssues;

    NYql::TIssues issues;
    NYql::IssuesFromMessage(op.issues(), issues);

    if (op.ready() != true) {
        issues.AddIssue(MakeIssue(NKikimrIssues::TIssuesIds::DEFAULT_ERROR, TStringBuilder()
            << "Unexpected operation for \"sync\" mode"));
        return ResultFromIssues<IKikimrGateway::TGenericResult>(TIssuesIds::DEFAULT_ERROR, issues);
    } else {
        const auto& yqlStatus = NYql::YqlStatusFromYdbStatus(op.status());
        return ResultFromIssues<IKikimrGateway::TGenericResult>(yqlStatus, issues);
    }
}

void DoAlterTableSameMailbox(Ydb::Table::AlterTableRequest&& req, TAlterTableRespHandler&& cb,
    const TString& database, const TMaybe<TString>& token, const TMaybe<TString>& type)
{
    NRpcService::DoLocalRpcSameMailbox<NGRpcService::TEvPgAlterTableRequest>(std::move(req), std::move(cb),
        database, token, type, TlsActivationContext->AsActorContext());
}

}
}
