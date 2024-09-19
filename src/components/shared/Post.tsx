import React from 'react'
import { css } from '@emotion/css'
import { Link } from 'gatsby'

const Styles = {
  article: css`
    margin-bottom: 32px;
  `,
  link: css`
    &:hover {
      text-decoration: underline;
      text-decoration-color: red;
    }
  `,
  h2: css`
    color: red;
  `,
  p: css`
    color: black;
  `,
  date: css`
    color: darkgray;
  `,
}

interface PostProps {
  post: {
    frontmatter: {
      path: string
      title: string
      date: string
    }
    excerpt: string
  }
}

const Post: React.FC<PostProps> = ({ post }) => {
  return (
    <article className={Styles.article}>
      <Link to={`/blog/${post.frontmatter.path}`} className={Styles.link}>
        <h2 className={Styles.h2}>{post.frontmatter.title}</h2>
      </Link>
      <p className={Styles.p}>{post.excerpt}</p>
      <small className={Styles.date}>{post.frontmatter.date}</small>
    </article>
  )
}

export default Post
