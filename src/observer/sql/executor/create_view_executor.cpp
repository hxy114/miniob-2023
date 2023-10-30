
#include "sql/executor/create_view_executor.h"
#include "session/session.h"
#include "storage/table/table.h"
#include "sql/stmt/create_view_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "storage/db/db.h"

RC CreateViewExecutor::execute(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  Stmt *stmt = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_VIEW, 
         "create view executor can not run this command: %d", static_cast<int>(stmt->type()));

  CreateViewStmt *create_view_stmt = static_cast<CreateViewStmt *>(stmt);

  Db *db = session->get_current_db();

  std::string view_name = create_view_stmt->view_name();
  Table *table = new Table(view_name,create_view_stmt->select_stmt(),create_view_stmt->field_metas()
    ,create_view_stmt->origin_fields(), create_view_stmt->can_insert(),create_view_stmt->can_update());

  db->set_table(view_name, table);
  return rc;
}