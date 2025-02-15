/*
 * Copyright The OpenTelemetry Authors
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OTEL_CLR_PROFILER_INTEGRATION_LOADER_H_
#define OTEL_CLR_PROFILER_INTEGRATION_LOADER_H_

#include <fstream>
#include <locale>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_set>
#include <vector>

#include "integration.h"
#include "macros.h"

namespace trace
{

using json = nlohmann::json;

class LoadIntegrationConfiguration {
public:
  LoadIntegrationConfiguration(bool traces_enabled,
                               std::vector<WSTRING> enabled_trace_integration_names,
                               bool metrics_enabled,
                               std::vector<WSTRING> enabled_metric_integration_names,
                               bool logs_enabled,
                               std::vector<WSTRING> enabled_log_integration_names)
    : traces_enabled(traces_enabled),
      enabledTraceIntegrationNames(std::move(enabled_trace_integration_names)),
      metrics_enabled(metrics_enabled),
      enabledMetricIntegrationNames(std::move(enabled_metric_integration_names)),
      logs_enabled(logs_enabled),
      enabledLogIntegrationNames(std::move(enabled_log_integration_names)) {
  }

  const bool traces_enabled;
  const std::vector<WSTRING> enabledTraceIntegrationNames;
  const bool metrics_enabled;
  const std::vector<WSTRING> enabledMetricIntegrationNames;
  const bool logs_enabled;
  const std::vector<WSTRING> enabledLogIntegrationNames;
};

// LoadIntegrationsFromEnvironment loads integrations from any files specified
// in the OTEL_DOTNET_AUTO_INTEGRATIONS_FILE environment variable
void LoadIntegrationsFromEnvironment(
    std::vector<IntegrationMethod>& integrationMethods,
    const LoadIntegrationConfiguration& configuration);

// LoadIntegrationsFromFile loads the integrations from a file
void LoadIntegrationsFromFile(
    const WSTRING& file_path,
    std::vector<IntegrationMethod>& integrationMethods,
    const LoadIntegrationConfiguration& configuration);

// LoadIntegrationsFromFile loads the integrations from a stream
void LoadIntegrationsFromStream(
    std::istream& stream,
    std::vector<IntegrationMethod>& integrationMethods,
    const LoadIntegrationConfiguration& configuration);

namespace
{
    void IntegrationFromJson(const json::value_type& src,
                         std::unordered_set<IntegrationMethod>& integrationMethods,
                         const LoadIntegrationConfiguration& configuration);

    void MethodReplacementFromJson(const json::value_type& src, const WSTRING& integrationName,
                                   std::unordered_set<IntegrationMethod>& integrationMethods);

    MethodReference MethodReferenceFromJson(const json::value_type& src, const bool is_target_method,
                                            const bool is_wrapper_method);

} // namespace

} // namespace trace

#endif
