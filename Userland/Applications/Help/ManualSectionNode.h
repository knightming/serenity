/*
 * Copyright (c) 2019-2020, Sergey Bugaev <bugaevc@serenityos.org>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "ManualNode.h"

class ManualSectionNode : public ManualNode {
public:
    virtual ~ManualSectionNode() override = default;

    ManualSectionNode(DeprecatedString section, DeprecatedString name)
        : m_section(section)
        , m_full_name(DeprecatedString::formatted("{}. {}", section, name))
    {
    }

    virtual NonnullOwnPtrVector<ManualNode>& children() const override
    {
        reify_if_needed();
        return m_children;
    }

    virtual ManualNode const* parent() const override { return nullptr; }
    virtual DeprecatedString name() const override { return m_full_name; }
    virtual bool is_open() const override { return m_open; }
    void set_open(bool open);

    DeprecatedString const& section_name() const { return m_section; }
    DeprecatedString path() const;

private:
    void reify_if_needed() const;

    DeprecatedString m_section;
    DeprecatedString m_full_name;
    mutable NonnullOwnPtrVector<ManualNode> m_children;
    mutable bool m_reified { false };
    bool m_open { false };
};
