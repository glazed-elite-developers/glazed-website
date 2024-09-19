import React, { FC } from 'react'
import Post from './Post'

interface PostType {
  id: string
}

interface BlogProps {
  posts: PostType[]
}

const Blog: FC<BlogProps> = ({ posts }) => {
  const renderPosts = posts.map((post) => <Post key={post.id} post={post} />)

  return (
    <div>
      <h1>Blog</h1>
      {renderPosts}
    </div>
  )
}

export default Blog
