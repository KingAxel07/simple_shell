#include "shell.h"

/**
 * _update_env_var - updates an environment variable with the given value
 * @env: pointer to the environment variables
 * @var_name: name of the variable to update
 * @value: new value to set for the variable
 */
void _update_env_var(char **env, const char *var_name, const char *value)
{
	char *var_prefix = NULL;
	int var_prefix_len = 0;

	// Prepare the variable prefix, e.g., "PWD=" or "OLDPWD="
	var_prefix_len = _strlen(var_name);
	var_prefix = malloc(var_prefix_len + 1);
	if (!var_prefix)
		return;
	_strcpy(var_prefix, var_name);

	// Concatenate the prefix with the new value to get the full string
	char *full_var = str_concat(var_prefix, value);
	free(var_prefix);

	if (!full_var)
		return;

	// Find the existing environment variable and update it with the new value
	for (int i = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], var_name, var_prefix_len) == 0)
		{
			// If the new value is shorter, update the existing string
			int new_value_len = _strlen(value);
			if (new_value_len < _strlen(env[i] + var_prefix_len))
			{
				_strcpy(env[i] + var_prefix_len, value);
			}
			else
			{
				// Otherwise, allocate new memory and copy the new value
				free(env[i]);
				env[i] = malloc(_strlen(full_var) + 1);
				if (!env[i])
				{
					free(full_var);
					return;
				}
				_strcpy(env[i], full_var);
			}
			break;
		}
	}

	free(full_var);
}

/**
 * _updatepwd - changes the OLDPWD environment variable
 * @buf: pointer to old pwd
 * @myenv: copy of environmental variable
 */
void _updatepwd(char *buf, char **myenv)
{
	_update_env_var(myenv, "PWD=", buf);
}

/**
 * _updateoldpwd - changes the OLDPWD environment variable
 * @buf: pointer to old pwd
 * @myenv: copy of environmental variable
 */
void _updateoldpwd(char *buf, char **myenv)
{
	_update_env_var(myenv, "OLDPWD=", buf);
}

