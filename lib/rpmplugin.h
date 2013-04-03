#ifndef _RPMPLUGIN_H
#define _RPMPLUGIN_H

#include <rpm/rpmtypes.h>
#include <rpm/rpmfi.h>

/** \ingroup rpmplugin
 * Rpm plugin API 
 */

/* indicates the way the scriptlet is executed */
typedef enum rpmScriptletExecutionFlow_e {
    RPMSCRIPTLET_NONE    = 0,
    RPMSCRIPTLET_FORK    = 1 << 0, 
    RPMSCRIPTLET_EXEC    = 1 << 1
} rpmScriptletExecutionFlow;


/** \ingroup rpmfi
 * File disposition flags during package install/erase transaction.
 * XXX: Move these to rpmfi.h once things stabilize.
 */
enum rpmFileActionFlags_e {
    /* bits 0-15 reserved for actions */
    FAF_UNOWNED		= (1 << 31)
};
typedef rpmFlags rpmFileActionFlags;

/** \ingroup rpmfi
 * File action and associated flags on install/erase
 */
typedef rpmFlags rpmFsmOp;

#define XFA_MASK	0x0000ffff
#define XFAF_MASK	~(XFA_MASK)
#define XFO_ACTION(_a)	((_a) & XFA_MASK)	/*!< File op action part */
#define XFO_FLAGS(_a)	((_a) & XFAF_MASK)	/*!< File op flags part */

/* plugin hook typedefs */
typedef rpmRC (*plugin_init_func)(rpmts ts,
				 const char * name, const char * opts);
typedef void (*plugin_cleanup_func)(void);
typedef rpmRC (*plugin_opente_func)(rpmte te);
typedef rpmRC (*plugin_coll_post_any_func)(void);
typedef rpmRC (*plugin_coll_post_add_func)(void);
typedef rpmRC (*plugin_coll_pre_remove_func)(void);
typedef rpmRC (*plugin_tsm_pre_func)(rpmts ts);
typedef rpmRC (*plugin_tsm_post_func)(rpmts ts, int res);
typedef rpmRC (*plugin_psm_pre_func)(rpmte te);
typedef rpmRC (*plugin_psm_post_func)(rpmte te, int res);
typedef rpmRC (*plugin_scriptlet_pre_func)(const char *s_name, int type);
typedef rpmRC (*plugin_scriptlet_fork_post_func)(const char *path, int type);
typedef rpmRC (*plugin_scriptlet_post_func)(const char *s_name, int type,
					    int res);
typedef rpmRC (*plugin_fsm_file_pre_func)(const char* path, mode_t file_mode,
					  rpmFsmOp op);
typedef rpmRC (*plugin_fsm_file_post_func)(const char* path, mode_t file_mode,
					  rpmFsmOp op, int res);
typedef rpmRC (*plugin_fsm_file_prepare_func)(const char* path,
					      const char *dest,
					      mode_t file_mode, rpmFsmOp op);

typedef struct rpmPluginHooks_s * rpmPluginHooks;
struct rpmPluginHooks_s {
    /* plugin constructor and destructor hooks */
    plugin_init_func			init;
    plugin_cleanup_func			cleanup;
    /* collection plugin hooks */
    plugin_opente_func			opente;
    plugin_coll_post_any_func		coll_post_any;
    plugin_coll_post_add_func		coll_post_add;
    plugin_coll_pre_remove_func		coll_pre_remove;
    /* per transaction plugin hooks */
    plugin_tsm_pre_func			tsm_pre;
    plugin_tsm_post_func		tsm_post;
    /* per transaction element hooks */
    plugin_psm_pre_func			psm_pre;
    plugin_psm_post_func		psm_post;
    /* per scriptlet hooks */
    plugin_scriptlet_pre_func		scriptlet_pre;
    plugin_scriptlet_fork_post_func	scriptlet_fork_post;
    plugin_scriptlet_post_func		scriptlet_post;
    /* per file hooks */
    plugin_fsm_file_pre_func		fsm_file_pre;
    plugin_fsm_file_post_func		fsm_file_post;
    plugin_fsm_file_prepare_func	fsm_file_prepare;
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif /* _RPMPLUGIN_H */
