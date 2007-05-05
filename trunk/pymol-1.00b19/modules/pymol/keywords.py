
import parsing
import cmd

def get_command_keywords(self_cmd=cmd):
    return {
        # keyword : [ command, # min_arg, max_arg, separator, mode ]

        # NOTE: min_arg, max_arg, and separator, are hold-overs from the
        #       original PyMOL parser which will eventually be removed.
        #       all new commands should use NO_CHECK or STRICT modes
        #       which make much better use of built-in python features.
        'abort'         : [ self_cmd.abort             , 0 , 0 , ''  , parsing.ABORT ],
        'accept'        : [ self_cmd.accept            , 0 , 0 , ''  , parsing.STRICT ],
        'alias'         : [ self_cmd.alias             , 0 , 0 , ''  , parsing.LITERAL1 ], # insecure
        'align'         : [ self_cmd.align             , 0 , 0 , ''  , parsing.STRICT ],
        'alter'         : [ self_cmd.alter             , 0 , 0 , ''  , parsing.LITERAL1 ], # insecure
        'alter_state'   : [ self_cmd.alter_state       , 0 , 0 , ''  , parsing.LITERAL2 ], # insecure
        'angle'         : [ self_cmd.angle             , 0 , 0 , ''  , parsing.STRICT ],          
        'as'            : [ self_cmd.show_as           , 0 , 0 , ''  , parsing.STRICT ],          
        'assert'        : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ], 
        'attach'        : [ self_cmd.attach            , 0 , 0 , ''  , parsing.STRICT ],
        'backward'      : [ self_cmd.backward          , 0 , 0 , ''  , parsing.STRICT ],
        'bg_color'      : [ self_cmd.bg_color          , 0 , 0 , ''  , parsing.STRICT ],
        'bmp'           : [ self_cmd.bmp               , 0 , 0 , ''  , parsing.SECURE ], # BMP save image support *NJK*
        'bond'          : [ self_cmd.bond              , 0 , 0 , ''  , parsing.STRICT ],
        'break'         : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],   
        'button'        : [ self_cmd.button            , 0 , 0 , ''  , parsing.STRICT ],
        'cartoon'       : [ self_cmd.cartoon           , 0 , 0 , ''  , parsing.STRICT ],
        'cd'            : [ self_cmd.cd                , 0 , 0 , ''  , parsing.STRICT ],
        'center'        : [ self_cmd.center            , 0 , 0 , ''  , parsing.STRICT ],     
        'check'         : [ self_cmd.check             , 0 , 0 , ''  , parsing.STRICT ],
        'class'         : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ], 
        'clip'          : [ self_cmd.clip              , 0 , 0 , ''  , parsing.STRICT ],
        'cls'           : [ self_cmd.cls               , 0 , 0 , ''  , parsing.STRICT ],
        'color'         : [ self_cmd.color             , 0 , 0 , ''  , parsing.STRICT ],
        'commands'      : [ self_cmd.helping.commands  , 0 , 0 , ''  , parsing.STRICT ],
        'config_mouse'  : [ self_cmd.config_mouse      , 0 , 0 , ''  , parsing.STRICT ],
        'continue'      : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'copy'          : [ self_cmd.copy              , 0 , 0 , ''  , parsing.LEGACY ],
        'count_atoms'   : [ self_cmd.count_atoms       , 0 , 0 , ''  , parsing.STRICT ],
        'count_frames'  : [ self_cmd.count_frames      , 0 , 0 , ''  , parsing.STRICT ],   
        'count_states'  : [ self_cmd.count_states      , 0 , 0 , ''  , parsing.STRICT ],
        'cycle_valence' : [ self_cmd.cycle_valence     , 0 , 0 , ''  , parsing.STRICT ],
        'create'        : [ self_cmd.create            , 0 , 0 , ''  , parsing.LEGACY ],
        'decline'       : [ self_cmd.decline           , 0 , 0 , ''  , parsing.STRICT ],      
        'delete'        : [ self_cmd.delete            , 0 , 0 , ''  , parsing.STRICT ],
        'def'           : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],   
        'del'           : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'deprotect'     : [ self_cmd.deprotect         , 0 , 0 , ''  , parsing.STRICT ],
        'deselect'      : [ self_cmd.deselect          , 0 , 0 , ''  , parsing.STRICT ],
        'dihedral'      : [ self_cmd.dihedral          , 0 , 0 , ''  , parsing.STRICT ],
        'dir'           : [ self_cmd.ls                , 0 , 0 , ''  , parsing.STRICT ],
        'disable'       : [ self_cmd.disable           , 0 , 0 , ''  , parsing.STRICT ],
        'distance'      : [ self_cmd.distance          , 0 , 0 , ''  , parsing.LEGACY ],
        'drag'          : [ self_cmd.drag              , 0 , 0 , ''  , parsing.STRICT ],            
        'draw'          : [ self_cmd.draw              , 0 , 0 , ''  , parsing.STRICT ],
        'dss'           : [ self_cmd.dss               , 0 , 0 , ''  , parsing.STRICT ],
        'dump'          : [ self_cmd.dump              , 0 , 0 , ''  , parsing.STRICT ],
        'dummy'         : [ self_cmd.dummy             , 0 , 0 , ''  , parsing.STRICT ],   
        'edit'          : [ self_cmd.edit              , 0 , 0 , ''  , parsing.STRICT ],
        'edit_mode'     : [ self_cmd.edit_mode         , 0 , 0 , ''  , parsing.STRICT ],
        'elif'          : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'else'          : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'embed'         : [ self_cmd.dummy             , 0 , 3 , ',' , parsing.EMBED  ],
        'enable'        : [ self_cmd.enable            , 0 , 0 , ''  , parsing.STRICT ],
        'ending'        : [ self_cmd.ending            , 0 , 0 , ''  , parsing.STRICT ],
        'except'        : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],      
        'extract'       : [ self_cmd.extract           , 0 , 0 , ''  , parsing.STRICT ],            
        'exec'          : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],   
        'export_dots'   : [ self_cmd.export_dots       , 0 , 0 , ''  , parsing.STRICT ],
        'extend'        : [ self_cmd.extend            , 0 , 0 , ''  , parsing.STRICT ],
        'fast_minimize' : [ self_cmd.fast_minimize     , 1,  4 , ',' , parsing.SIMPLE ], # TO REMOVE
        'feedback'      : [ self_cmd.feedback          , 0,  0 , ''  , parsing.STRICT ],
        'fetch'         : [ self_cmd.fetch             , 0,  0 , ''  , parsing.STRICT ],
        'fit'           : [ self_cmd.fit               , 0 , 0 , ''  , parsing.STRICT ],
        'finally'       : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'fix_chemistry' : [ self_cmd.fix_chemistry     , 0 , 0 , ''  , parsing.STRICT ],
        'flag'          : [ self_cmd.flag              , 0 , 0 , ''  , parsing.LEGACY ],
        'for'           : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'fork'          : [ self_cmd.helping.spawn     , 1 , 2 , ',' , parsing.SPAWN  ],
        'forward'       : [ self_cmd.forward           , 0 , 0 , ''  , parsing.STRICT ],
        'fragment'      : [ self_cmd.fragment          , 0 , 0 , ''  , parsing.STRICT ],
        'full_screen'   : [ self_cmd.full_screen       , 0 , 0 , ''  , parsing.STRICT ],
        'fuse'          : [ self_cmd.fuse              , 0 , 0 , ''  , parsing.STRICT ],
        'frame'         : [ self_cmd.frame             , 0 , 0 , ''  , parsing.STRICT ],
        'get'           : [ self_cmd.get               , 0 , 0 , ''  , parsing.STRICT ],
        'get_angle'     : [ self_cmd.get_angle         , 0 , 0 , ''  , parsing.STRICT ],      
        'get_area'      : [ self_cmd.get_area          , 0 , 0 , ''  , parsing.STRICT ],
        'get_chains'    : [ self_cmd.get_chains        , 0 , 0 , ''  , parsing.STRICT ],
        'get_dihedral'  : [ self_cmd.get_dihedral      , 0 , 0 , ''  , parsing.STRICT ],
        'get_distance'  : [ self_cmd.get_distance      , 0 , 0 , ''  , parsing.STRICT ],
        'get_extent'    : [ self_cmd.get_extent        , 0 , 0 , ''  , parsing.STRICT ],
        'get_position'  : [ self_cmd.get_position      , 0 , 0 , ''  , parsing.STRICT ],
        'get_symmetry'  : [ self_cmd.get_symmetry      , 0 , 0 , ''  , parsing.STRICT ],
        'get_title'     : [ self_cmd.get_title         , 0 , 0 , ''  , parsing.STRICT ],   
        'get_type'      : [ self_cmd.get_type          , 0 , 0 , ''  , parsing.STRICT ],
        'get_version'   : [ self_cmd.get_version       , 0 , 0 , ''  , parsing.STRICT ],            
        'get_view'      : [ self_cmd.get_view          , 0 , 0 , ''  , parsing.STRICT ],
        'global'        : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'gradient'      : [ self_cmd.gradient          , 0 , 0 , ''  , parsing.STRICT ],            
        'group'         : [ self_cmd.group             , 0 , 0 , ''  , parsing.STRICT ],
        'h_add'         : [ self_cmd.h_add             , 0 , 0 , ''  , parsing.STRICT ],
        'h_fill'        : [ self_cmd.h_fill            , 0 , 0 , ''  , parsing.STRICT ],
        'h_fix'         : [ self_cmd.h_fix             , 0 , 0 , ''  , parsing.STRICT ],            
        'help'          : [ self_cmd.help              , 0 , 0 , ''  , parsing.STRICT ],
        'hide'          : [ self_cmd.hide              , 0 , 0 , ''  , parsing.STRICT ],
        'id_atom'       : [ self_cmd.id_atom           , 0 , 0 , ''  , parsing.STRICT ],
        'identify'      : [ self_cmd.identify          , 0 , 0 , ''  , parsing.STRICT ],
        'if'            : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'import'        : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],   
        'index'         : [ self_cmd.index             , 0 , 0 , ''  , parsing.STRICT ],
        'indicate'      : [ self_cmd.indicate          , 0 , 0 , ''  , parsing.STRICT ],   
        'intra_fit'     : [ self_cmd.intra_fit         , 0 , 0 , ''  , parsing.STRICT ],
        'intra_rms'     : [ self_cmd.intra_rms         , 0 , 0 , ''  , parsing.STRICT ],
        'intra_rms_cur' : [ self_cmd.intra_rms_cur     , 0 , 0 , ''  , parsing.STRICT ],
        'invert'        : [ self_cmd.invert            , 0 , 0 , ''  , parsing.STRICT ],
        'isodot'        : [ self_cmd.isodot            , 0 , 0 , ''  , parsing.LEGACY ],
        'isolevel'      : [ self_cmd.isolevel           , 0 , 0 , '' , parsing.STRICT ],      
        'isomesh'       : [ self_cmd.isomesh           , 0 , 0 , ''  , parsing.LEGACY ],
        'isosurface'    : [ self_cmd.isosurface        , 0 , 0 , ''  , parsing.LEGACY ],   
        'iterate'       : [ self_cmd.iterate           , 0 , 0 , ''  , parsing.LITERAL1 ], # insecure
        'iterate_state' : [ self_cmd.iterate_state     , 0 , 0 , ''  , parsing.LITERAL2 ], # insecure
        'label'         : [ self_cmd.label             , 0 , 0 , ''  , parsing.LITERAL1 ], # insecure
        'load'          : [ self_cmd.load              , 0 , 0 , ''  , parsing.STRICT ],
        'space'         : [ self_cmd.space             , 0 , 0 , ''  , parsing.STRICT ],
        'load_embedded' : [ self_cmd.load_embedded     , 0 , 0 , ''  , parsing.STRICT ],
        'load_png'      : [ self_cmd.load_png          , 0 , 0 , ''  , parsing.STRICT ],
        'load_traj'     : [ self_cmd.load_traj         , 0 , 0 , ''  , parsing.STRICT ],
        'log'           : [ self_cmd.log               , 0 , 0 , ''  , parsing.STRICT ],
        'log_close'     : [ self_cmd.log_close         , 0 , 0 , ''  , parsing.STRICT ],
        'log_open'      : [ self_cmd.log_open          , 0 , 0 , ''  , parsing.STRICT ],
        'ls'            : [ self_cmd.ls                , 0 , 0 , ''  , parsing.STRICT ],
        'madd'          : [ self_cmd.madd              , 0 , 0 , ''  , parsing.STRICT ],
        'mask'          : [ self_cmd.mask              , 0 , 0 , ''  , parsing.STRICT ],
        'map_set'       : [ self_cmd.map_set           , 0 , 0 , ''  , parsing.STRICT ],
        'map_set_border': [ self_cmd.map_set_border    , 0 , 0 , ''  , parsing.STRICT ],
        'map_double'    : [ self_cmd.map_double        , 0 , 0 , ''  , parsing.STRICT ],
        'map_halve'     : [ self_cmd.map_halve         , 0 , 0 , ''  , parsing.STRICT ],            
        'map_new'       : [ self_cmd.map_new           , 0 , 0 , ''  , parsing.STRICT ],    
        'map_trim'      : [ self_cmd.map_trim          , 0 , 0 , ''  , parsing.STRICT ],                  
        'mappend'       : [ self_cmd.mappend           , 2 , 2 , ':' , parsing.MOVIE  ],
        'matrix_reset'  : [ self_cmd.matrix_reset      , 0 , 0 , ''  , parsing.STRICT ],         
        'matrix_copy'   : [ self_cmd.matrix_copy       , 0 , 0 , ''  , parsing.STRICT ],
        'matrix_transfer': [ self_cmd.matrix_copy       , 0 , 0 , ''  , parsing.STRICT ], # LEGACY
        'mem'           : [ self_cmd.mem               , 0 , 0 , ''  , parsing.STRICT ],
        'meter_reset'   : [ self_cmd.meter_reset       , 0 , 0 , ''  , parsing.STRICT ],
        'move'          : [ self_cmd.move              , 0 , 0 , ''  , parsing.STRICT ],
        'mset'          : [ self_cmd.mset              , 0 , 0 , ''  , parsing.STRICT ],
        'mdo'           : [ self_cmd.mdo               , 2 , 2 , ':' , parsing.MOVIE  ],
        'mdump'         : [ self_cmd.mdump             , 0 , 0 , ''  , parsing.STRICT ],      
        'mpng'          : [ self_cmd.mpng              , 0 , 0 , ''  , parsing.SECURE ],
        'mplay'         : [ self_cmd.mplay             , 0 , 0 , ''  , parsing.STRICT ],
        'mtoggle'       : [ self_cmd.mtoggle           , 0 , 0 , ''  , parsing.STRICT ],         
        'mray'          : [ self_cmd.mray              , 0 , 0 , ''  , parsing.STRICT ],
        'mstop'         : [ self_cmd.mstop             , 0 , 0 , ''  , parsing.STRICT ],
        'mclear'        : [ self_cmd.mclear            , 0 , 0 , ''  , parsing.STRICT ],
        'middle'        : [ self_cmd.middle            , 0 , 0 , ''  , parsing.STRICT ],
        'minimize'      : [ self_cmd.minimize          , 0 , 4 , ',' , parsing.SIMPLE ], # TO REMOVE
        'mmatrix'       : [ self_cmd.mmatrix           , 0 , 0 , ''  , parsing.STRICT ],
        'mouse'         : [ self_cmd.mouse             , 0 , 0 , ''  , parsing.STRICT ],
        'multisave'     : [ self_cmd.multisave         , 0 , 0 , ''  , parsing.STRICT ],
        'mview'         : [ self_cmd.mview             , 0 , 0 , ''  , parsing.STRICT ],
        'origin'        : [ self_cmd.origin            , 0 , 0 , ''  , parsing.STRICT ],
        'orient'        : [ self_cmd.orient            , 0 , 0 , ''  , parsing.STRICT ],
        'overlap'       : [ self_cmd.overlap           , 0 , 0 , ''  , parsing.STRICT ],
        'pair_fit'      : [ self_cmd.pair_fit          , 2 ,98 , ',' , parsing.SIMPLE ],
        'pass'          : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'phi_psi'       : [ self_cmd.phi_psi           , 0 , 0 , ''  , parsing.STRICT ],
        'pop'           : [ self_cmd.pop               , 0 , 0 , ''  , parsing.STRICT ],
        'protect'       : [ self_cmd.protect           , 0 , 0 , ''  , parsing.STRICT ],
        'pseudoatom'    : [ self_cmd.pseudoatom        , 0 , 0 , ''  , parsing.STRICT ],
        'push_undo'     : [ self_cmd.push_undo         , 0 , 0 , ''  , parsing.STRICT ],   
        'pwd'           : [ self_cmd.pwd               , 0 , 0 , ''  , parsing.STRICT ],
        'python'        : [ self_cmd.dummy             , 0 , 2 , ',' , parsing.PYTHON_BLOCK ],
        'skip'          : [ self_cmd.dummy             , 0 , 1 , ',' , parsing.SKIP ],
        'raise'         : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'ramp_new'      : [ self_cmd.ramp_new          , 0 , 0 , ''  , parsing.STRICT ],      
        'ray'           : [ self_cmd.ray               , 0 , 0 , ''  , parsing.STRICT ],
        'rebuild'       : [ self_cmd.rebuild           , 0 , 0 , ''  , parsing.STRICT ],
        'recolor'       : [ self_cmd.recolor           , 0 , 0 , ''  , parsing.STRICT ],   
        'redo'          : [ self_cmd.redo              , 0 , 0 , ''  , parsing.STRICT ],
        'reinitialize'  : [ self_cmd.reinitialize      , 0 , 0 , ''  , parsing.STRICT ],      
        'refresh'       : [ self_cmd.refresh           , 0 , 0 , ''  , parsing.STRICT ],
        'refresh_wizard': [ self_cmd.refresh_wizard    , 0 , 0 , ''  , parsing.STRICT ],
        'remove'        : [ self_cmd.remove            , 0 , 0 , ''  , parsing.STRICT ],
        'remove_picked' : [ self_cmd.remove_picked     , 0 , 0 , ''  , parsing.STRICT ],
        'rename'        : [ self_cmd.rename            , 0 , 0 , ''  , parsing.STRICT ],
        'order'         : [ self_cmd.order             , 0 , 0 , ''  , parsing.STRICT ],
        'replace'       : [ self_cmd.replace           , 0 , 0 , ''  , parsing.STRICT ],
        'replace_wizard': [ self_cmd.replace_wizard    , 0 , 0 , ''  , parsing.STRICT ],
        'reset'         : [ self_cmd.reset             , 0 , 0 , ''  , parsing.STRICT ],
        'resume'        : [ self_cmd.resume            , 0 , 0 , ''  , parsing.STRICT ],
        'return'        : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],   
        'rewind'        : [ self_cmd.rewind            , 0 , 0 , ''  , parsing.STRICT ],
        #      'rgbfunction'   : [ self_cmd.rgbfunction       , 0 , 0 , ''  , parsing.LEGACY ],         
        'rock'          : [ self_cmd.rock              , 0 , 0 , ''  , parsing.STRICT ],
        'rotate'        : [ self_cmd.rotate            , 0 , 0 , ''  , parsing.STRICT ],
        'run'           : [ self_cmd.helping.run       , 1 , 2 , ',' , parsing.RUN    ], # insecure
        'rms'           : [ self_cmd.rms               , 0 , 0 , ''  , parsing.STRICT ],
        'rms_cur'       : [ self_cmd.rms_cur           , 0 , 0 , ''  , parsing.STRICT ],
        'save'          : [ self_cmd.save              , 0 , 0 , ''  , parsing.SECURE ],
        'scene'         : [ self_cmd.scene             , 0 , 0 , ''  , parsing.STRICT ],
        'sculpt_purge'  : [ self_cmd.sculpt_purge      , 0 , 0 , ''  , parsing.STRICT ],   
        'sculpt_deactivate': [ self_cmd.sculpt_deactivate,0, 0 , ''  , parsing.STRICT ],
        'sculpt_activate': [ self_cmd.sculpt_activate  , 0 , 0 , ''  , parsing.STRICT ],
        'sculpt_iterate': [ self_cmd.sculpt_iterate    , 0 , 0 , ''  , parsing.STRICT ],
        'spectrum'      : [ self_cmd.spectrum          , 0 , 0 , ''  , parsing.STRICT ],
        'select'        : [ self_cmd.select            , 0 , 0 , ''  , parsing.LEGACY ],
        'set'           : [ self_cmd.set               , 0 , 0 , ''  , parsing.LEGACY ],
        'set_bond'      : [ self_cmd.set_bond          , 0 , 0 , ''  , parsing.STRICT ],
        'set_color'     : [ self_cmd.set_color         , 0 , 0 , ''  , parsing.LEGACY ],
        'set_dihedral'  : [ self_cmd.set_dihedral      , 0 , 0 , ''  , parsing.STRICT ],
        'set_name'      : [ self_cmd.set_name          , 0 , 0 , ''  , parsing.STRICT ],
        'set_geometry'  : [ self_cmd.set_geometry      , 0 , 0 , ''  , parsing.STRICT ],
        'set_symmetry'  : [ self_cmd.set_symmetry      , 0 , 0 , ''  , parsing.STRICT ],         
        'set_title'     : [ self_cmd.set_title         , 0 , 0 , ''  , parsing.STRICT ],   
        'set_key'       : [ self_cmd.set_key           , 0 , 0 , ''  , parsing.STRICT ], # API only
        'set_view'      : [ self_cmd.set_view          , 0 , 0 , ''  , parsing.STRICT ],   
        'show'          : [ self_cmd.show              , 0 , 0 , ''  , parsing.STRICT ],
        'slice_new'     : [ self_cmd.slice_new         , 0 , 0 , ''  , parsing.STRICT ],
        #      'slice_lock'    : [ self_cmd.slice_lock        , 0 , 0 , ''  , parsing.LEGACY ],
        #      'slice_unlock'  : [ self_cmd.slice_unlock      , 0 , 0 , ''  , parsing.LEGACY ],
        'smooth'        : [ self_cmd.smooth            , 0 , 0 , ''  , parsing.STRICT ],
        'sort'          : [ self_cmd.sort              , 0 , 0 , ''  , parsing.STRICT ],
        'spawn'         : [ self_cmd.helping.spawn     , 1 , 2 , ',' , parsing.SPAWN  ], # insecure
        'spheroid'      : [ self_cmd.spheroid          , 0 , 0 , ''  , parsing.STRICT ],
        'splash'        : [ self_cmd.splash            , 0 , 0 , ''  , parsing.STRICT ],
        'split_states'  : [ self_cmd.split_states      , 0 , 0 , ''  , parsing.STRICT ],
        '_special'      : [ self_cmd._special          , 0 , 0 , ''  , parsing.STRICT ],
        'stereo'        : [ self_cmd.stereo            , 0 , 0 , ''  , parsing.STRICT ],
        'symexp'        : [ self_cmd.symexp            , 0 , 0 , ''  , parsing.LEGACY ],
        'system'        : [ self_cmd.system            , 0 , 0 , ''  , parsing.LITERAL ],
        'test'          : [ self_cmd.test              , 0 , 0 , ''  , parsing.STRICT ],
        'toggle'        : [ self_cmd.toggle            , 0 , 0 , ''  , parsing.STRICT ],      
        'torsion'       : [ self_cmd.torsion           , 0 , 0 , ''  , parsing.STRICT ], # vs toggle_object
        'translate'     : [ self_cmd.translate         , 0 , 0 , ''  , parsing.STRICT ],
        'try'           : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],
        'turn'          : [ self_cmd.turn              , 0 , 0 , ''  , parsing.STRICT ],
        'quit'          : [ self_cmd.quit              , 0 , 0 , ''  , parsing.STRICT ],
        '_quit'         : [ self_cmd._quit             , 0 , 0 , ''  , parsing.STRICT ],
        'png'           : [ self_cmd.png               , 0 , 0 , ''  , parsing.SECURE ],
        'unbond'        : [ self_cmd.unbond            , 0 , 0 , ''  , parsing.STRICT ],
        'unpick'        : [ self_cmd.unpick            , 0 , 0 , ''  , parsing.STRICT ],
        'undo'          : [ self_cmd.undo              , 0 , 0 , ''  , parsing.STRICT ],
        'ungroup'       : [ self_cmd.ungroup           , 0 , 0 , ''  , parsing.STRICT ],
        'unmask'        : [ self_cmd.unmask            , 0 , 0 , ''  , parsing.STRICT ],
        'unprotect'     : [ self_cmd.deprotect         , 0 , 0 , ''  , parsing.STRICT ],
        'unset'         : [ self_cmd.unset             , 0 , 0 , ''  , parsing.STRICT ],
        'unset_bond'    : [ self_cmd.unset_bond        , 0 , 0 , ''  , parsing.STRICT ],               
        'update'        : [ self_cmd.update            , 0 , 0 , ''  , parsing.STRICT ],
        'vdw_fit'       : [ self_cmd.vdw_fit           , 0 , 0 , ''  , parsing.STRICT ],   
        'view'          : [ self_cmd.view              , 0 , 0 , ''  , parsing.STRICT ],   
        'viewport'      : [ self_cmd.viewport          , 0 , 0 , ''  , parsing.STRICT ],
        'vmouse'        : [ self_cmd.vmouse            , 0 , 0 , ''  , parsing.STRICT ], # Virtual mouse support *NJK*
        'window'        : [ self_cmd.window            , 0 , 0 , ''  , parsing.STRICT ],         
        'while'         : [ self_cmd.python_help       , 0 , 0 , ''  , parsing.PYTHON ],   
        'wizard'        : [ self_cmd.wizard            , 0 , 0 , ''  , parsing.STRICT ],
        'zoom'          : [ self_cmd.zoom              , 0 , 0 , ''  , parsing.STRICT ],
        # utility programs
        'util.cbag'     : [ self_cmd.util.cbag         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbac'     : [ self_cmd.util.cbac         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbay'     : [ self_cmd.util.cbay         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbas'     : [ self_cmd.util.cbas         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbap'     : [ self_cmd.util.cbap         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbak'     : [ self_cmd.util.cbak         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbaw'     : [ self_cmd.util.cbaw         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbab'     : [ self_cmd.util.cbab         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbao'     : [ self_cmd.util.cbao         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbam'     : [ self_cmd.util.cbam         , 0 , 0 , ''  , parsing.STRICT ],
        'util.cbc'      : [ self_cmd.util.cbc          , 0 , 0 , ''  , parsing.STRICT ],
        'util.chainbow' : [ self_cmd.util.chainbow     , 0 , 0 , ''  , parsing.STRICT ],
        'util.colors'   : [ self_cmd.util.colors       , 0 , 0 , ''  , parsing.STRICT ],
        'util.mrock'    : [ self_cmd.util.mrock        , 0 , 0 , ''  , parsing.STRICT ], # LEGACY
        'util.mroll'    : [ self_cmd.util.mroll        , 0 , 0 , ''  , parsing.STRICT ], # LEGACY
        'util.ss'       : [ self_cmd.util.ss           , 0 , 0 , ''  , parsing.STRICT ],# secondary structure
        'util.rainbow'  : [ self_cmd.util.rainbow      , 0 , 0 , ''  , parsing.STRICT ],
        # movie programs
        'movie.rock'    : [ self_cmd.movie.rock        , 0 , 0 , ''  , parsing.STRICT ],
        'movie.roll'    : [ self_cmd.movie.roll        , 0 , 0 , ''  , parsing.STRICT ],
        'movie.load'    : [ self_cmd.movie.load        , 0 , 0 , ''  , parsing.STRICT ],
        'movie.zoom'    : [ self_cmd.movie.zoom        , 0 , 0 , ''  , parsing.STRICT ],
        'movie.screw'   : [ self_cmd.movie.screw       , 0 , 0 , ''  , parsing.STRICT ],
        'movie.sweep'   : [ self_cmd.movie.sweep       , 0 , 0 , ''  , parsing.STRICT ],
        'movie.pause'   : [ self_cmd.movie.pause       , 0 , 0 , ''  , parsing.STRICT ],               
        'movie.nutate'  : [ self_cmd.movie.nutate      , 0 , 0 , ''  , parsing.STRICT ],
        'movie.tdroll'  : [ self_cmd.movie.tdroll      , 0 , 0 , ''  , parsing.STRICT ],
        # activate metaphorics extensions
        #   'metaphorics'   : [ self_cmd.metaphorics       , 0 , 0 , ''  , parsing.STRICT ],
        }

def get_help_only_keywords(self_cmd=cmd):
    return {  
        'api'                   : [ self_cmd.helping.api ],
        'editing'               : [ self_cmd.helping.editing ],  
        'edit_keys'             : [ self_cmd.helping.edit_keys ],
        'examples'              : [ self_cmd.helping.examples ],
        'faster'                : [ self_cmd.helping.faster ],
        'get_area'              : [ self_cmd.get_area ],
        'get_movie_playing'     : [ self_cmd.get_movie_playing ],
        'get_model'             : [ self_cmd.get_model ],
        'get_mtl_obj'           : [ self_cmd.get_mtl_obj ],
        'get_names'             : [ self_cmd.get_names ],
        'get_object_list'       : [ self_cmd.get_object_list ],
        'get_object_matrix'     : [ self_cmd.get_object_matrix ],
        'get_povray'            : [ self_cmd.get_povray  ],
        'get_pdbstr'            : [ self_cmd.get_pdbstr ],
        'get_symmetry'          : [ self_cmd.get_symmetry ],
        'get_title'             : [ self_cmd.get_title  ],
        'get_type'              : [ self_cmd.get_type   ],
        'get_version'           : [ self_cmd.get_version  ],            
        'keyboard'              : [ self_cmd.helping.keyboard   ],
        'launching'             : [ self_cmd.helping.launching  ],
        'load_model'            : [ self_cmd.load_model  ],
        'mouse'                 : [ self_cmd.helping.mouse  ],
        'movies'                : [ self_cmd.helping.movies  ],
        'python_help'           : [ self_cmd.python_help   ],        
        'povray'                : [ self_cmd.helping.povray  ],
        'read_molstr'           : [ self_cmd.read_molstr ],
        'read_pdbstr'           : [ self_cmd.read_pdbstr ],      
        'release'               : [ self_cmd.helping.release ],   
        'selections'            : [ self_cmd.helping.selections ],
        'sync'                  : [ self_cmd.sync ],
        'transparency'          : [ self_cmd.helping.transparency ],
        '@'                     : [ self_cmd.helping.at_sign ],  
        }
