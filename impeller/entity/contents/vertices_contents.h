// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_IMPELLER_ENTITY_CONTENTS_VERTICES_CONTENTS_H_
#define FLUTTER_IMPELLER_ENTITY_CONTENTS_VERTICES_CONTENTS_H_

#include <functional>
#include <memory>
#include <vector>

#include "flutter/fml/macros.h"
#include "impeller/core/sampler_descriptor.h"
#include "impeller/entity/contents/contents.h"
#include "impeller/entity/entity.h"
#include "impeller/entity/geometry/geometry.h"
#include "impeller/entity/geometry/vertices_geometry.h"
#include "impeller/geometry/color.h"
#include "impeller/geometry/path.h"
#include "impeller/geometry/point.h"

namespace impeller {

class VerticesContents final : public Contents {
 public:
  VerticesContents();

  ~VerticesContents() override;

  void SetGeometry(std::shared_ptr<VerticesGeometry> geometry);

  void SetAlpha(Scalar alpha);

  void SetBlendMode(BlendMode blend_mode);

  void SetSourceContents(std::shared_ptr<Contents> contents);

  std::shared_ptr<VerticesGeometry> GetGeometry() const;

  const std::shared_ptr<Contents>& GetSourceContents() const;

  // |Contents|
  std::optional<Rect> GetCoverage(const Entity& entity) const override;

  // |Contents|
  bool Render(const ContentContext& renderer,
              const Entity& entity,
              RenderPass& pass) const override;

 private:
  Scalar alpha_;
  std::shared_ptr<VerticesGeometry> geometry_;
  BlendMode blend_mode_ = BlendMode::kSource;
  std::shared_ptr<Contents> src_contents_;

  VerticesContents(const VerticesContents&) = delete;

  VerticesContents& operator=(const VerticesContents&) = delete;
};

class VerticesColorContents final : public Contents {
 public:
  explicit VerticesColorContents(const VerticesContents& parent);

  ~VerticesColorContents() override;

  // |Contents|
  std::optional<Rect> GetCoverage(const Entity& entity) const override;

  // |Contents|
  bool Render(const ContentContext& renderer,
              const Entity& entity,
              RenderPass& pass) const override;

  void SetAlpha(Scalar alpha);

 private:
  const VerticesContents& parent_;
  Scalar alpha_ = 1.0;

  VerticesColorContents(const VerticesColorContents&) = delete;

  VerticesColorContents& operator=(const VerticesColorContents&) = delete;
};

class VerticesUVContents final : public Contents {
 public:
  explicit VerticesUVContents(const VerticesContents& parent);

  ~VerticesUVContents() override;

  // |Contents|
  std::optional<Rect> GetCoverage(const Entity& entity) const override;

  // |Contents|
  bool Render(const ContentContext& renderer,
              const Entity& entity,
              RenderPass& pass) const override;

  void SetAlpha(Scalar alpha);

 private:
  const VerticesContents& parent_;
  Scalar alpha_ = 1.0;

  VerticesUVContents(const VerticesUVContents&) = delete;

  VerticesUVContents& operator=(const VerticesUVContents&) = delete;
};

/// A vertices contents for per-color vertices + texture and porter duff
/// blended.
class VerticesSimpleBlendContents final : public Contents {
 public:
  VerticesSimpleBlendContents();

  ~VerticesSimpleBlendContents() override;

  void SetGeometry(std::shared_ptr<VerticesGeometry> geometry);

  void SetAlpha(Scalar alpha);

  void SetBlendMode(BlendMode blend_mode);

  void SetTexture(std::shared_ptr<Texture> texture);

  void SetSamplerDescriptor(SamplerDescriptor descriptor);

  void SetTileMode(Entity::TileMode tile_mode_x, Entity::TileMode tile_mode_y);

  void SetEffectTransform(Matrix transform);

  // |Contents|
  std::optional<Rect> GetCoverage(const Entity& entity) const override;

  // |Contents|
  bool Render(const ContentContext& renderer,
              const Entity& entity,
              RenderPass& pass) const override;

 private:
  Scalar alpha_ = 1.0;
  std::shared_ptr<VerticesGeometry> geometry_;
  std::shared_ptr<Texture> texture_;
  BlendMode blend_mode_ = BlendMode::kSource;
  SamplerDescriptor descriptor_ = {};
  Entity::TileMode tile_mode_x_ = Entity::TileMode::kClamp;
  Entity::TileMode tile_mode_y_ = Entity::TileMode::kClamp;
  Matrix inverse_matrix_ = {};

  VerticesSimpleBlendContents(const VerticesSimpleBlendContents&) = delete;

  VerticesSimpleBlendContents& operator=(const VerticesSimpleBlendContents&) =
      delete;
};

}  // namespace impeller

#endif  // FLUTTER_IMPELLER_ENTITY_CONTENTS_VERTICES_CONTENTS_H_
