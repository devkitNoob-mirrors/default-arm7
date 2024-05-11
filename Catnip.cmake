
catnip_package(default_arm7)

macro(_arm7_preset _name)
	catnip_add_preset(${_name}
		DEFAULT
		TOOLSET NDS
		PROCESSOR armv4t
		BUILD_TYPE MinSizeRel
		CACHE ENABLE_LOG=OFF ${ARGN}
	)

	catnip_add_preset(${_name}_dbg
		TOOLSET NDS
		PROCESSOR armv4t
		BUILD_TYPE MinSizeRel
		CACHE ENABLE_LOG=ON ${ARGN}
	)
endmacro()

_arm7_preset(sphynx)

_arm7_preset(lykoi
	ENABLE_BLKDEV=ON
)

_arm7_preset(bobtail
	ENABLE_WLMGR=ON
)

_arm7_preset(ragdoll
	ENABLE_BLKDEV=ON
	ENABLE_WLMGR=ON
	ENABLE_SOUND=ON
)

_arm7_preset(maine
	ENABLE_BLKDEV=ON
	ENABLE_WLMGR=ON
	ENABLE_SOUND=ON
	ENABLE_MAXMOD=ON
)
