set(HOOK_SOURCE "${CMAKE_SOURCE_DIR}/scripts/git-hooks/pre-push/pre-push")
set(HOOK_DEST_DIR "${CMAKE_SOURCE_DIR}/.git/hooks") set(HOOK_DEST
"${HOOK_DEST_DIR}")

add_custom_target(install-git-hook ALL COMMAND ${CMAKE_COMMAND} -E
make_directory "${HOOK_DEST_DIR}"

COMMAND ${CMAKE_COMMAND} -E copy "${HOOK_SOURCE}" "${HOOK_DEST}"

COMMAND chmod a+x "${HOOK_DEST}"

COMMAND ${CMAKE_COMMAND} -E echo "Git hook installed successfully"

COMMENT "Installing git pre-push hook" VERBATIM )

# Проверка существования исходного файла хука if(NOT EXISTS "${HOOK_SOURCE}")
message(WARNING "Git hook source not found: ${HOOK_SOURCE}") endif()
